#pragma once

#include "CoreMinimal.h"
#include "QuestInterface.h"
#include "Quest/QuestDataAsset.h"
#include "QuestSystemInterface.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestSystemCompleted);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestSystemUpdated);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestSystemChanged, TScriptInterface<IQuestInterface>, NewQuest);

// This class does not need to be modified.
UINTERFACE(NotBlueprintable)
class UQuestSystemInterface : public UInterface
{
	GENERATED_BODY()
};

class GP4_LYMBO_API IQuestSystemInterface
{
	GENERATED_BODY()

public:
	/// 
	/// @param QuestInstigator The controller that instigated the quest. Most likely the player controller.
	/// @param QuestData The quest to set.
	/// 
	UFUNCTION(BlueprintCallable)
	virtual void SetQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData) = 0;
	// TODO: Does TScriptInterface support const types?
	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IQuestInterface> GetQuest() const = 0;

public:
	virtual FOnQuestSystemCompleted& GetOnQuestSystemCompletedHandle() = 0;
	virtual FOnQuestSystemUpdated& GetOnQuestSystemUpdatedHandle() = 0;
	virtual FOnQuestSystemChanged& GetOnQuestSystemChangedHandle() = 0;
};