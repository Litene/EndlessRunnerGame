#pragma once

#include "DrawDebugHelpers.h"

#define CONSOLE_LOG(Text) UE_LOG(LogTemp, Warning, TEXT(Text)))
#define SCREEN_LOG(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Cyan, Text)
#define DRAW_SSPHERE(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.0f, 24, FColor::Cyan, false, -1.0f)
#define DRAW_SPHERE(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.0f, 24, FColor::Cyan, true)
#define DRAW_SLINE(Start, End) if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, FColor::Red ,false, -1.0f , 0, 2)
#define DRAW_LINE(Start, End) if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, FColor::Red ,true,-1.0f, 0, 2)
#define DRAW_SRAY(Start, Direction) if(GetWorld()) DrawDebugLine(GetWorld(), Start, Start + Direction.GetSafeNormal() * 30, FColor::Red ,false, -1.0f, 0, 1)
#define DRAW_RAY(Start, Direction) if(GetWorld()) DrawDebugLine(GetWorld(), Start, Start + Direction.GetSafeNormal() * 30, FColor::Red ,false, -1.0f, 0, 1)
#define DRAW_SPOINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.0f, FColor::Cyan, false, -1.0f)
#define DRAW_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.0f, FColor::Cyan, true)
#define DRAW_SVECTOR(Start, End) \
if(GetWorld())\
{\
DrawDebugLine(GetWorld(), Start, Start + End, FColor::Red ,false,-1.0f, 0, 2);\
DrawDebugPoint(GetWorld(), Start + End, 15.0f, FColor::Cyan, false, -1.0f);\
}
#define DRAW_VECTOR(Start, End) \
if(GetWorld())\
{\
DrawDebugLine(GetWorld(), Start, Start + End, FColor::Red ,true,-1.0f, 0, 2);\
DrawDebugPoint(GetWorld(), Start + End, 15.0f, FColor::Cyan, true);\
}

// these two downs are wrong