// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARPGCharacter::ARPGCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

    // set our turn rates for input
    BaseTurnRate = 45.f;

    // don't rotate when the controller rotates. -- let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    // configure character movement
    // character moves in the direction of input
    GetCharacterMovement()->bOrientRotationToMovement = true;
    // at this rotation rate
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);

    // create a camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    // the camera follows at this distance behind the character
    CameraBoom->TargetArmLength = 300.f;
    CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
    // rotate the arm based on the controller
    CameraBoom->bUsePawnControlRotation = true;

    // create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    // camera does not rotate relative to arm
    FollowCamera->bUsePawnControlRotation = false;
    FollowCamera->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

    /* Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
     * are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++) */
}

// Input
void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindAxis(TEXT("MoveForward"), this, &ARPGCharacter::MoveForward);
    InputComponent->BindAxis(TEXT("MoveRight"), this, &ARPGCharacter::MoveRight);

    /* we have two versions of rotation bindings to handle different kinds of devices differently
     * "turn" handles devices that provide an absolute delta, such as a mouse. "turnrate" is for
     * devices that we choose to treat as a rate of change, such as an analog joystick */
    InputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
    InputComponent->BindAxis(TEXT("TurnRate"), this, &ARPGCharacter::TurnAtRate);
}

void ARPGCharacter::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARPGCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ARPGCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && Value != 0.f)
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawDirection(0.f, Rotation.Yaw, 0.f);

        // get right vector
        const FVector Direction = FRotationMatrix(YawDirection).GetUnitAxis(EAxis::Y);

        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}



// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ARPGCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}