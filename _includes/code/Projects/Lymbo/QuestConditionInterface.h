#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestConditionInterface.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestConditionMet, TScriptInterface<IQuestConditionInterface>, ConditionMet);

// This class does not need to be modified.
UINTERFACE()
class UQuestConditionInterface : public UInterface
{
	GENERATED_BODY()
};

class GP4_LYMBO_API IQuestConditionInterface
{
	GENERATED_BODY()

	// Called when condition is started/exited.
public:
	UFUNCTION(BlueprintNativeEvent)
	void InitCondition(const AController* QuestInstigator = nullptr);
	UFUNCTION(BlueprintNativeEvent)
	void ExitCondition();
	
public:
	virtual FString GetConditionName() const = 0;
	virtual FOnQuestConditionMet& GetOnConditionMetHandle() = 0;
};