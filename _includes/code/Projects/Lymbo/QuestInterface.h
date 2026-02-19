#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Quest/QuestDataAsset.h"
#include "UObject/Interface.h"
#include "QuestInterface.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestCompleted);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestUpdated);

// This class does not need to be modified.
UINTERFACE(NotBlueprintable)
class UQuestInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GP4_LYMBO_API IQuestInterface
{
	GENERATED_BODY()

public:
	virtual void InitQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData){}
	virtual void ExitQuest(){}

public:
	UFUNCTION(BlueprintCallable)
	virtual FString GetQuestName() const = 0;

	UFUNCTION(BlueprintCallable)
	virtual FGameplayTag GetQuestStartedTag() const = 0;
	UFUNCTION(BlueprintCallable)
	virtual FGameplayTag GetQuestFinishedTag() const = 0;

public:
	UFUNCTION(BlueprintCallable)
	virtual int GetNrOfCompletions() const = 0;
	UFUNCTION(BlueprintCallable)
	virtual int GetNrOfConditions() const = 0;

public:
	UFUNCTION(BlueprintCallable)
	virtual FString GetConditionDescription(int ConditionIndex) const = 0;

public:
	virtual FOnQuestCompleted& GetOnQuestCompletedHandle() = 0;
	virtual FOnQuestUpdated& GetOnQuestUpdatedHandle() = 0;
};