#pragma once

#include "CoreMinimal.h"
#include "DialogueSystemInterface.h"
#include "Systems/Dialogue/DataAsset/DialogueDataAsset.h"
#include "Systems/Dialogue/DialogueContext/GameDialogueContext.h"
#include "UObject/Object.h"
#include "DialogueSystem.generated.h"

UCLASS()
class GP4_LYMBO_API UDialogueSystem : public UObject, public IDialogueSystemInterface
{
	GENERATED_BODY()

public:
	void SetDialogueDataSystem(TScriptInterface<IDialogueDataInterface> SomeDialogueDataSystem);

public:
	void ResetDialogueSystem();

public:
	virtual void InitiateDialogue(UDialogueDataAsset* SomeDialogueAsset, APlayerController* PlayerController) override;
	virtual FDialogueResult ProgressDialogue() override;
	virtual void ExitDialogue() override;

public:
	virtual void SelectOption(int OptionIndex) override;

public:
	virtual FOnDialogueSet& GetOnDialogueSetHandle() override;
	virtual FOnDialogueInitiated& GetOnDialogueInitiatedHandle() override;
	virtual FOnDialogueProgressed& GetOnDialogueProgressedHandle() override;
	virtual FOnDialogueExited& GetOnDialogueExitedHandle() override;

public:
	UPROPERTY(BlueprintAssignable, Category="Dialogue/Events")
	FOnDialogueSet OnDialogueSet;
	UPROPERTY(BlueprintAssignable, Category="Dialogue/Events")
	FOnDialogueInitiated OnDialogueInitiated;
	UPROPERTY(BlueprintAssignable, Category="Dialogue/Events")
	FOnDialogueProgressed OnDialogueProgressed;
	UPROPERTY(BlueprintAssignable, Category="Dialogue/Events")
	FOnDialogueExited OnDialogueExited;

private:
	UPROPERTY()
	TScriptInterface<IDialogueDataInterface> DialogueDataSystem;

private:
	FGameDialogueContext DialogueContext;

private:
	UPROPERTY()
	TObjectPtr<UDialogueDataAsset> DialogueAsset;
	int CurrentNodeIndex = 0;
	TMap<FString, int> LabelToIndexMap;

private:
	UPROPERTY()
	TMap<TObjectPtr<UDialogueDataAsset>, int> PreviousDialoguesIndicesMap;

private:
	void SetUpLabels();
};