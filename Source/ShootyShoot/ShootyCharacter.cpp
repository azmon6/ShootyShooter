// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootyCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ShootyShootGameModeBase.h"

// Sets default values
AShootyCharacter::AShootyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShootyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	//Spawning actors at runtime that the character uses
	GunOfCharacter = GetWorld()->SpawnActor<AGun>(GunClass);

	//HIDE GUN FROM SKELETON CAUSE WE WANT TO SPAWN ONE FROM BLUEPRINT
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	GunOfCharacter->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("GunSocket"));
	GunOfCharacter->SetOwner(this);
}

// Called every frame
void AShootyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AShootyCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}


// Called to bind functionality to input
void AShootyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//GAMEPAD SUPPORT REMOVED FOR BUGGY BEHAVIOR

	//BIND MOVEMENT FORWARD/BACKWARD AXIS
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &AShootyCharacter::MoveForward);

	//BIND MOVEMENT RIGHT/LEFT AXIS
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShootyCharacter::MoveRight);

	//BIND CAMERA MOVEMENT Z AXIS
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShootyCharacter::LookUp);

	//BIND CAMERA MOVEMENT X AXIS
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShootyCharacter::LookRight);

	//BIND JUMP USING DEFAULT JUMP ACTION FOR EASY USE AND EASY MODIFICATION THROUGH BLUEPRINT
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	//BIND Shooting
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShootyCharacter::Shoot);
}

float AShootyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	//IF DEAD WE DISABLE THE CAPSULE 
	if (IsDead())
	{
		
		//NOTIFY GAME WORLD OF DEATH
		AShootyShootGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShootyShootGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		// REMOVE COLLISION OF DEAD THINGS
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}


	return DamageToApply;
}

bool AShootyCharacter::IsDead() const
{
	return Health <= 0;
}


void AShootyCharacter::MoveForward(float Value)
{
	// Move Character forward with simple vector * value
	AddMovementInput(GetActorForwardVector() * Value);
}

void AShootyCharacter::MoveRight(float Value)
{
	//Move Character right with simple vector * value
	AddMovementInput(GetActorRightVector() * Value);
}

void AShootyCharacter::LookUp(float Value)
{
	//Pitch is Up and Down
	AddControllerPitchInput(Value);
}

void AShootyCharacter::LookRight(float Value)
{
	//Yaw is left and right
	AddControllerYawInput(Value);
}

void AShootyCharacter::Shoot()
{
	GunOfCharacter->ShootTrigger();
}

