#ifndef EFFECTS_H
#define EFFECTS_H

#include <Arduino.h>
#include <LEDMatrix.h>
#include <SW_Timer.h>


namespace LEDArrangement
{

namespace Effects
{





// ---------------- LED_effect ----------------

class LED_effect // Oberklasse für Effekte
{
	public:
		LED_effect(LEDMatrix& Mat, const uint32_t Delay_between_frames);

        // Matrix für Effect vorbereiten
        // z.B. Pixel initialieren
		virtual bool setup_LED_Matrix() = 0;

        // nächstes Bild berechnen und in Pixel-Array speichern
        // aber noch nicht an Matrix übertragen
		virtual bool render_next_frame() = 0;

        // Prüfen ob seid dem letzten Frame genug Zeit vergangen ist 
        // Um das nächst Frame zu berechen.
        // Falls ja, wird das neue Frame berechent und true zurückgegeben
        // Falls nein, wird direkt false zurückgegeben. 
		virtual bool update_frame(const uint32_t currentTime = 0);

	protected:

		LEDMatrix& mat;
		SW_Timer effect_update_timer;
};










} // Ende namespace Effects

} // Ende namespace LEDArrangement

#endif