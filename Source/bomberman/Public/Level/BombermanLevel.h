// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BombermanLevel.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABombermanLevel : public ALevelScriptActor
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> ToSpawn;

	UFUNCTION(BlueprintCallable)
	void OnPlayerEliminated();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfPlayers = 0;

	UFUNCTION(BlueprintImplementableEvent, Category = "Bomberman")
	void OnPlayersSpawned();

	// Dlaration d'un ement vide
	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnPlayerSpawned(APawn* SpawnedPawn); // Cet ement peut re implentdans le Blueprint

};
