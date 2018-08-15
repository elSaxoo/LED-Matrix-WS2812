#ifndef RAINBOW_H
#define RAINBOW_H

#include <Arduino.h>
#include <LEDMatrix.h>
#include <Effects.h>
#include <FontBitmap.h>
namespace LEDArrangement
{

namespace Effects
{



// ---------------- Rainbow ----------------
class Rainbow : public LED_effect
{

    public:

        Rainbow(LEDMatrix& Mat, const uint32_t Delay_between_frames, 
            const int32_t omega_x, const int32_t omega_y, 
            const int32_t k_x, const int32_t k_y, 
            const int32_t phi_x = 0, const int32_t phi_y = 0, 
            const uint8_t saturation = 255, const uint8_t value = 255);
        
        Rainbow(LEDMatrix& Mat, const uint32_t Delay_between_frames);



        // Matrix für Effect vorbereiten
        // z.B. Pixel initialieren
		bool setup();

        // nächstes Bild berechnen und in Pixel-Array speichern
        // aber noch nicht an Matrix übertragen
		bool render_next_frame();

        // Prüfen ob seid dem letzten Frame genug Zeit vergangen ist 
        // Um das nächst Frame zu berechen.
        // Falls ja, wird das neue Frame berechent und true zurückgegeben
        // Falls nein, wird direkt false zurückgegeben. 
		bool update_frame(const uint32_t currentTime = 0);


        // Wellenzahl für x-Richtung und y-Richtung automatisch ausrechen
        Rainbow& auto_scale_kx_ky();
        Rainbow& auto_scale_kx_ky(const int32_t max_phase);
        Rainbow& auto_scale_kx_ky(const bool reverse_x, const bool reverse_y);
        Rainbow& auto_scale_kx_ky(const int32_t max_phase, const bool reverse_x, const bool reverse_y);

        // Getter
        // Parameter für Sinus-Welle
        int32_t get_omega_x() const { return this->omega_x; }
        int32_t get_omega_y() const { return this->omega_y; }
        int32_t get_k_x() const { return this->k_x; }
        int32_t get_k_y() const { return this->k_y; }
        int32_t get_phi_x() const { return this->phi_x; }
        int32_t get_phi_y() const { return this->phi_y; }
        // Parameter für Farbe
        uint8_t get_saturation() const { return this->saturation; }
        uint8_t get_value() const { return this->value; }

        // Setter
        // Parameter für Sinus-Welle
        Rainbow& set_omega_x(int32_t omega_x) { this->omega_x = omega_x; return *this; }
        Rainbow& set_omega_y(int32_t omega_y) { this->omega_y = omega_y; return *this; }
        Rainbow& set_k_x(int32_t k_x) { this->k_x = k_x; return *this; }
        Rainbow& set_k_y(int32_t k_y) { this->k_y = k_y; return *this; }
        Rainbow& set_phi_x(int32_t phi_x) { this->phi_x = phi_x; return *this; }
        Rainbow& set_phi_y(int32_t phi_y) { this->phi_y = phi_y; return *this; }

        // Parameter für Farbe
        Rainbow& set_saturation(uint8_t saturation) { this->saturation = saturation; return *this; }
        Rainbow& set_value(uint8_t value) { this->value = value; return *this; }

        // Wellenrichtung invetieren
        Rainbow& reverse_omega_x() { this->omega_x = -(this->omega_x); return *this;}
        Rainbow& reverse_omega_y() { this->omega_y = -(this->omega_y); return *this;}
        Rainbow& reverse_k_x() { this->k_x = -(this->k_x); return *this;}
        Rainbow& reverse_k_y() { this->k_y = -(this->k_y); return *this;}



    private:

        // In Abhängigkeit von der Pixelposition (x, y), 
        // der Wellenzahl für x-Richtung und y-Richtung 
        // und den Phasen-Offsets für x-Richtung und y-Richtung 
        // die zugehörige Farbe berechnen
        CHSV calc_color(const int32_t x, const int32_t y, const int32_t k_x, const int32_t k_y, const int32_t phi_x, const int32_t phi_y, const uint8_t saturation = 255, const uint8_t value = 255) const;
        
        // Für all Pixel der Matrix die Farbe berechen mit der Methode calc_color
        void calc_sine_wave(const int32_t k_x, const int32_t k_y, const int32_t phi_x, const int32_t phi_y, const uint8_t saturation = 255, const uint8_t value = 255);

        // Parameter für Sinus-Welle
        int32_t omega_x;
        int32_t omega_y;
        int32_t k_x;
        int32_t k_y;
        int32_t phi_x;
        int32_t phi_y;

        // Parameter für Farbe
        uint8_t saturation;
        uint8_t value;

};


} // Ende namespace Effects

} // Ende namespace LEDArrangement

#endif // RAINBOW_H