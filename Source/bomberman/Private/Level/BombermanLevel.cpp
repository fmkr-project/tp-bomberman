// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/BombermanLevel.h"
#include "GameFramework/InputDeviceLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void ABombermanLevel::BeginPlay()
{
	Super::BeginPlay();

	if (!ToSpawn)
	{
		return;
	}

	TArray<FInputDeviceId> ConnectedDevices;
	UInputDeviceLibrary::GetAllConnectedInputDevices(ConnectedDevices);
	
	NumberOfPlayers = ConnectedDevices.Num();

	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	if (PlayerStarts.Num() <= 0)
	{
		return;
	}

	for (int32 i = 0; i < ConnectedDevices.Num(); i++)
	{
		if (auto PlayerStart = Cast<APlayerStart>(PlayerStarts[i]))
		{
			APawn* Pawn = GetWorld()->SpawnActor<APawn>(ToSpawn, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());

			if (auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), i))
			{
				PlayerController->Possess(Pawn);
			}
			else
			{
				APlayerController* Controller = UGameplayStatics::CreatePlayer(GetWorld(), i);
				Controller->Possess(Pawn);
			}
			// Appelle lvnement Blueprint aprs le spawn du joueur
			OnPlayerSpawned(Pawn);

		}
	}
	// Appeler l'vnement Blueprint aprs le spawn des joueurs
	OnPlayersSpawned();
}

void ABombermanLevel::OnPlayerEliminated()
{
	NumberOfPlayers--;
}
