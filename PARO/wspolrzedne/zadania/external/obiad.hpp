#pragma once
#include <future>
#include <chrono>
#include <thread>

struct Obiad {};
struct SuroweZiemniaki {};
struct UgotowaneZiemniaki{};
struct SurowyKurczak{};
struct PokrojonySurowyKurczak{};
struct GotowyKurczak{};
struct Woda{};
struct TorebkaHerbaty{};
struct Herbata{};

inline void oczekiwanie() { std::this_thread::sleep_for(std::chrono::milliseconds(500)); }

inline Herbata zrob_herbate(Woda, TorebkaHerbaty) { oczekiwanie(); oczekiwanie(); return Herbata(); }
inline PokrojonySurowyKurczak pokroj_kurczaka(SurowyKurczak) { oczekiwanie(); return PokrojonySurowyKurczak(); }
inline GotowyKurczak usmaz_kurczaka(PokrojonySurowyKurczak) { oczekiwanie(); return GotowyKurczak(); }
inline UgotowaneZiemniaki ugotuj_ziemniaki(Woda, SuroweZiemniaki) { oczekiwanie(); oczekiwanie(); return UgotowaneZiemniaki(); }
inline Obiad zrob_obiad(UgotowaneZiemniaki, GotowyKurczak, Herbata) { return Obiad(); }

using Clock = std::chrono::high_resolution_clock;

inline Obiad synchroniczneGotowanie()
{
  return zrob_obiad(
                     ugotuj_ziemniaki( Woda(), SuroweZiemniaki() ),
                     usmaz_kurczaka( pokroj_kurczaka( SurowyKurczak() ) ),
                     zrob_herbate( Woda(), TorebkaHerbaty() )
                   );
}
