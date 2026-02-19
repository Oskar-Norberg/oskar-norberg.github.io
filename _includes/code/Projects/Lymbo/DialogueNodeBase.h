#pragma once

#include "CoreMinimal.h"
#include "Systems/Dialogue/DialogueContext/GameDialogueContext.h"
#include "Systems/Dialogue/DialogueResult/FDialogueResult.h"
#include "UObject/Object.h"
#include "DialogueNodeBase.generated.h"

UCLASS(Abstract, EditInlineNew)
class GP4_LYMBO_API UDialogueNodeBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue")
	TOptional<FString> Label;
	
public:
	virtual bool CanExecute(const FGameDialogueContext& DialogueContext) const { return true; }

	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) PURE_VIRTUAL(
		FDialogueResult, return FDialogueResult(););

	virtual void PickOption(const FGameDialogueContext& DialogueContext, int OptionIndex) PURE_VIRTUAL();

	virtual void ExecuteNode(FGameDialogueContext DialogueContext) { }
};
