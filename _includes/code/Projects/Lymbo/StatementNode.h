#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBase.h"
#include "GameplayTagContainer.h"
#include "StatementNode.generated.h"

UCLASS()
class GP4_LYMBO_API UStatementNode : public UDialogueNodeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue", meta = (Categories = "Speaker"))
	FGameplayTag SpeakerTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	FText Text = FText::GetEmpty();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue")
	TArray<FDialogueAnimationData> Animations;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	bool DoCloseDialogue = true;

	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
};
