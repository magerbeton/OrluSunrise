// Fill out your copyright notice in the Description page of Project Settings.


#include "TextFileManager.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

bool UTextFileManager::SaveStringText(FString SaveDirectory, FString Filename, FString Content, bool AllowOverwriting)
{
	// set complete file path.
	SaveDirectory += "\\";
	SaveDirectory += Filename;

	if (!AllowOverwriting)
	{
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			return false;
		}
	}

	FString FinalString = Content;

	return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory);

}

