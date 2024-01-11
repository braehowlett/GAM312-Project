#include "MutantEnemy.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "MutantAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"


// Sets default values
AMutantEnemy::AMutantEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCollisionDetection =
		CreateDefaultSubobject<USphereComponent>(TEXT("Player Collision Detection"));

	PlayerCollisionDetection->SetupAttachment(RootComponent);

	PlayerAttackCollisionDetection =
		CreateDefaultSubobject<USphereComponent>(TEXT("Player Attack Collision Detection"));

	PlayerAttackCollisionDetection->SetupAttachment(RootComponent);

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));

}

// Called when the game starts or when spawned
void AMutantEnemy::BeginPlay()
{
	Super::BeginPlay();

	MutantAIController = Cast<AMutantAIController>(GetController());

	(this, &AMutantEnemy::OnAIMoveCompleted);

	PlayerCollisionDetection->OnComponentBeginOverlap.AddDynamic(this,
		&AMutantEnemy::OnPlayerDetectedOverlapBegin);

	PlayerCollisionDetection->OnComponentEndOverlap.AddDynamic(this,
		&AMutantEnemy::OnPlayerDetectedOverlapEnd);

	PlayerAttackCollisionDetection->OnComponentBeginOverlap.AddDynamic(this,
		&AMutantEnemy::OnPlayerAttackOverlapBegin);

	PlayerAttackCollisionDetection->OnComponentEndOverlap.AddDynamic(this,
		&AMutantEnemy::OnPlayerAttackOverlapEnd);

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this,
		&AMutantEnemy::OnDealDamageOverlapBegin);

	AnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void AMutantEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMutantEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMutantEnemy::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (!PlayerDetected)
	{
		MutantAIController->RandomPatrol();
	}
	else if (PlayerDetected && CanAttackPlayer)
	{
		StopSeekingPlayer();

		// attack player
		AnimInstance->Montage_Play(EnemyAttackAnimation);
	}
}

void AMutantEnemy::MoveToPlayer()
{
	MutantAIController->MoveToLocation(PlayerREF->GetActorLocation(), StoppingDistance, true);
}

void AMutantEnemy::SeekPlayer()
{
	MoveToPlayer();
	GetWorld()->GetTimerManager().SetTimer(SeekPlayerTimerHandle, this,
		&AMutantEnemy::SeekPlayer, 0.25f, true);
}

void AMutantEnemy::StopSeekingPlayer()
{
	GetWorld()->GetTimerManager().ClearTimer(SeekPlayerTimerHandle);
}

void AMutantEnemy::OnPlayerDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerREF = Cast<APlayerCharacter>(OtherActor);
	if (PlayerREF)
	{
		PlayerDetected = true;
		SeekPlayer();
	}
}

void AMutantEnemy::OnPlayerDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerREF = Cast<APlayerCharacter>(OtherActor);
	if (PlayerREF)
	{
		PlayerDetected = false;
		StopSeekingPlayer();
		MutantAIController->RandomPatrol();
	}
}

void AMutantEnemy::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerREF = Cast<APlayerCharacter>(OtherActor);
	if (PlayerREF)
	{
		CanAttackPlayer = true;
	}
}

void AMutantEnemy::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerREF = Cast<APlayerCharacter>(OtherActor);
	if (PlayerREF)
	{
		CanAttackPlayer = false;

		// stop the attack animation and chase the player
		AnimInstance->Montage_Stop(0.0f, EnemyAttackAnimation);

		SeekPlayer();
	}
}

void AMutantEnemy::OnDealDamageOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerREF = Cast<APlayerCharacter>(OtherActor);
	if (PlayerREF && CanDealDamage)
	{
		// deal damage to player
		UE_LOG(LogTemp, Warning, TEXT("Player Damaged"));
	}
}

void AMutantEnemy::AttackAnimationEnded()
{
	if (CanAttackPlayer)
	{
		AnimInstance->Montage_Play(EnemyAttackAnimation);
	}
}