#pragma once

#include "CoreMinimal.h"
#include "Systems/Dialogue/DialogueResult/FDialogueResult.h"
#include "UObject/Interface.h"
#include "DialogueSystemInterface.generated.h"

class UDialogueDataAsset;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueSet);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueInitiated);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueProgressed, FDialogueResult, DialogueResult);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueExited);

// This class does not need to be modified.
UINTERFACE()
class UDialogueSystemInterface : public UInterface
{
	GENERATED_BODY()
};

class GP4_LYMBO_API IDialogueSystemInterface
{
	GENERATED_BODY()

public:
	virtual void InitiateDialogue(UDialogueDataAsset* SomeDialogueAsset, APlayerController* PlayerController) = 0;
	virtual FDialogueResult ProgressDialogue() = 0;
	virtual void ExitDialogue() = 0;
	
public:
	virtual void SelectOption(int OptionIndex) = 0;

public:
	virtual FOnDialogueSet& GetOnDialogueSetHandle() = 0;
	virtual FOnDialogueInitiated& GetOnDialogueInitiatedHandle() = 0;
	virtual FOnDialogueProgressed& GetOnDialogueProgressedHandle() = 0;
	virtual FOnDialogueExited& GetOnDialogueExitedHandle() = 0;
};