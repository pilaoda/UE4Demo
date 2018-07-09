# 分层有限状态机(HFSM)设计思路


## 1. MyCharacter

 - 首先需要设计自己的character类，在该类中绑定输入及对应操作。
```
class QUICISTART_API AMyCharacter : public ACharacter
```
 - 同时该类还需要包含一个UStateManager类来管理状态机
```
UStateManager* StateManager;
```
 - 当特定输入触发时，将调用StateManager的对应方法来切换状态。

## 2. BaseState

 - BaseState类是所有状态的基类，继承于UActorComponent，拥有并重载了其BeginPlay()及TickComponent()方法。
```
// Called when the game starts
void UBaseState::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s begin play"), *StateName);
}


// Called every frame
void UBaseState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("%s tick"), *StateName);
}
```
 - 同时还维护了一个成员变量用来记录状态名
```
FString StateName;
```

## 3. 继承自BaseState的子状态
 - 所有状态都继承BaseState，并在自己的构造函数中对状态名进行定义。
```
UStandState::UStandState()
{
	StateName = FString("stand_state");

}
```
 - 目前一共有Stand，Crouch，Creep，Move，Halt，Open，Close七种状态类
    - 其中Stand，Crouch，Creep属于一级状态，表示人物当前的姿势。
    - Move，Halt属于二级状态，表示人物当前是否在移动。
    - Open，Close属于三级状态，表示人物当前是否开启了瞄准镜。
 - 要表示一个人物完整的状态需要三个级别的状态共同组成

## 4. StateManager
 - StateManager负责管理角色所有状态之间的切换，是character的成员变量。
 - StateManager一共有六个状态的变量，包括当前三个级别的状态以及为了解决一些状态组合无法存在和声明的三个替换状态。
 - 实践时我注意到，要为想动态维护的变量加上UPROPERTY()，这些UBaseState对象才会被添加进UE4的GC系统引用中，否则将被创建于栈中而不被GC计数管理，指针随时可能失效。
```
        UPROPERTY()
            UBaseState* H1_State;
        UPROPERTY()
            UBaseState* H2_State;
        UPROPERTY()
            UBaseState* H3_State;

        UPROPERTY()
            UBaseState* H1_Replace_State;
        UPROPERTY()
            UBaseState* H2_Replace_State;
        UPROPERTY()
            UBaseState* H3_Replace_State;
```        
 - GetStateObject方法是根据状态名创建新状态对象的方法。
```
UBaseState* GetStateObject(FString StateName);
```
 - 切换状态时将调用类似以下方法创建新状态对象，来替换对应级别的状态对象。
```
void UStateManager::Stand() {
	FString StateName = "stand_state";
	H1_State = GetStateObject(StateName);
}
```
 - 需要对特殊的无法到达的状态组合进行判断，并标记三个级别替换状态为应该替换的状态组合。例如趴地+移动+开瞄准镜的组合应被替换为趴地+移动+关瞄准镜，来满足相应的游戏表现需求。同时原来记录的三个状态级别变量应保持不变，来保证该状态切换时仍能保留其进入之前的信息，例如趴地移动开镜时应该关镜，但停止移动后需要重新自动开镜。
```
// Called every frame
void UStateManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bReplaced = false;

	if (H1_State->StateName == "creep_state" && H2_State->StateName == "move_state"  && H3_State->StateName == "open_state")
	{
		H1_Replace_State = H1_State;
		H2_Replace_State = H2_State;
		H3_Replace_State = NewObject<UCloseState>();
		bReplaced = true;
	}
	else
	{
		H1_Replace_State = nullptr;
		H2_Replace_State = nullptr;
		H3_Replace_State = nullptr;
		bReplaced = false;
	}

	if (bReplaced)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current State Replaced: { H1:%s, H2:%s, H3:%s }"), *H1_Replace_State->StateName, *H2_Replace_State->StateName, *H3_Replace_State->StateName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Current State: { H1:%s, H2:%s, H3:%s }"), *H1_State->StateName, *H2_State->StateName, *H3_State->StateName);
	}
}
```
![状态替换](StateReplace.png)