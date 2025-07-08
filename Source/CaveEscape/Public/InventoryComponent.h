// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class APuzzleItemBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CAVEESCAPE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<APuzzleItemBase*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<TSubclassOf<APuzzleItemBase>> DefaultItemClasses;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 SelectedIndex;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(APuzzleItemBase* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SelectItemByIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	APuzzleItemBase* GetSelectedItem() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	const TArray<APuzzleItemBase*>& GetItems() const { return Items; }

	virtual void BeginPlay() override;
};