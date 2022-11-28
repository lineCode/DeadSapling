// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeadSaplingCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


#define TRACE_INTERACTIVE		ECC_GameTraceChannel2

//////////////////////////////////////////////////////////////////////////
// ADeadSaplingCharacter

ADeadSaplingCharacter::ADeadSaplingCharacter()
{
	// Set up tick for main character - so we can trace camera viewing direction all the time.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// set our trace properties 
	LineTraceDistance = 100000.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADeadSaplingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADeadSaplingCharacter::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADeadSaplingCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADeadSaplingCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADeadSaplingCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADeadSaplingCharacter::LookUpAtRate);
}

void ADeadSaplingCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADeadSaplingCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADeadSaplingCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADeadSaplingCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ADeadSaplingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Start;
	FVector End;

	FVector PlayerEyesLoc;
	FRotator PlayerEyesRot;

	GetActorEyesViewPoint(PlayerEyesLoc, PlayerEyesRot);

	Start = PlayerEyesLoc;
	End = PlayerEyesLoc + (PlayerEyesRot.Vector() * LineTraceDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, this);

	FHitResult InteractHit = FHitResult(ForceInit);

	bool bIsHit = GetWorld()->LineTraceSingleByChannel(InteractHit, Start, End, TRACE_INTERACTIVE, TraceParams);
	//DrawDebugLine(GetWorld(),Start,	End,FColor(255, 0, 0),false, 10, 0,12.333	);

	if (bIsHit)
	{
		LastInteractiveTraced = InteractHit.GetActor();
		IInteractiveActor::Execute_OnTrace(LastInteractiveTraced);
	}
	else
	{
		LastInteractiveTraced = nullptr;
	}
}

void ADeadSaplingCharacter::Interact()
{
	if (LastInteractiveTraced)
	{
		IInteractiveActor::Execute_Interact(LastInteractiveTraced);
	}
}
