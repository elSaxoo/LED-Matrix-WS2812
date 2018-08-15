#include <Rainbow.h>


namespace LEDArrangement
{

namespace Effects
{

// ---------------- Rainbow ----------------
Rainbow::Rainbow(LEDMatrix& Mat, const uint32_t Delay_between_frames)
:
    LED_effect(Mat, Delay_between_frames),
    // Parameter für Sinus-Welle
    omega_x(1),
    omega_y(1),
    k_x(1),
    k_y(1),
    phi_x(0),
    phi_y(0),
    // Parameter für Farbe
    saturation(255),
    value(255)
{
    this->auto_scale_kx_ky();
}



Rainbow::Rainbow(LEDMatrix& Mat, const uint32_t Delay_between_frames, 
    const int32_t omega_x, const int32_t omega_y, 
    const int32_t k_x, const int32_t k_y, 
    const int32_t phi_x, const int32_t phi_y, 
    const uint8_t saturation, const uint8_t value)
:
    LED_effect(Mat, Delay_between_frames),
    // Parameter für Sinus-Welle
    omega_x(omega_x),
    omega_y(omega_y),
    k_x(k_x),
    k_y(k_y),
    phi_x(phi_x),
    phi_y(phi_y),
    // Parameter für Farbe
    saturation(saturation),
    value(value)
{}




// Prüfen ob seid dem letzten Frame genug Zeit vergangen ist 
// Um das nächst Frame zu berechen.
// Falls ja, wird das neue Frame berechent und true zurückgegeben
// Falls nein, wird direkt false zurückgegeben. 
bool Rainbow::update_frame(const uint32_t currentTime)
{
    if (effect_update_timer(currentTime))
    {
        return	render_next_frame();
    }
    else
    {
        return false;
    }
}



// Matrix für Effect vorbereiten
// z.B. Pixel initialieren
bool Rainbow::setup()
{
    this->calc_sine_wave(this->k_x, this->k_y, this->phi_x, this->phi_y, this->saturation, this->value);
    return true;
}


// nächstes Bild berechnen und in Pixel-Array speichern
// aber noch nicht an Matrix übertragen
bool Rainbow::render_next_frame()
{
    this->calc_sine_wave(this->k_x, this->k_y, this->phi_x, this->phi_y, this->saturation, this->value);
    this->phi_x += this->omega_x;
    this->phi_y += this->omega_y;
    return true;
}


// Wellenzahl für x-Richtung und y-Richtung automatisch ausrechen
Rainbow& Rainbow::auto_scale_kx_ky()
{
    return this->auto_scale_kx_ky(255, false, false);
}
Rainbow& Rainbow::auto_scale_kx_ky(const int32_t max_phase)
{
    return this->auto_scale_kx_ky(max_phase, false, false);
}
Rainbow& Rainbow::auto_scale_kx_ky(const bool reverse_x, const bool reverse_y)
{
    return this->auto_scale_kx_ky(255, reverse_x, reverse_y);
}
Rainbow& Rainbow::auto_scale_kx_ky(const int32_t max_phase, const bool reverse_x, const bool reverse_y)
{
    const int32_t width = this->mat.matrix_width();
    const int32_t height = this->mat.matrix_height();

    if(reverse_x)
    {
        if(reverse_y)
        {
            this->k_x = (-1) * max_phase / width;
            this->k_y = (-1) * max_phase / height;
        }
        else
        {
            this->k_x = (-1) * max_phase / width;
            this->k_y =        max_phase / height;
        }
    }
    else
    {
        if(reverse_y)
        {
            this->k_x =        max_phase / width;
            this->k_y = (-1) * max_phase / height;
        }
        else
        {
            this->k_x = max_phase / width;
            this->k_y = max_phase / height;
        }
    }

    return *this;
}




// In Abhängigkeit von der Pixelposition (x, y), 
// der Wellenzahl für x-Richtung und y-Richtung 
// und den Phasen-Offsets für x-Richtung und y-Richtung 
// die zugehörige Farbe berechnen
CHSV Rainbow::calc_color(const int32_t x, const int32_t y, const int32_t k_x, const int32_t k_y, const int32_t phi_x, const int32_t phi_y, const uint8_t saturation, const uint8_t value) const
{
    uint8_t hue = ((x * k_x - phi_x) + (y * k_y - phi_y) % 256);
    return CHSV(hue, saturation, value);
}


// Für all Pixel der Matrix die Farbe berechen mit der Methode calc_color
void Rainbow::calc_sine_wave(const int32_t k_x, const int32_t k_y, const int32_t phi_x, const int32_t phi_y, const uint8_t saturation, const uint8_t value)
{
    const int32_t mat_height = this->mat.matrix_height();
    const int32_t mat_width = this->mat.matrix_width();

    for(int32_t y = 0; y < mat_height; ++y)
    {
        for(int32_t x = 0; x < mat_width; ++x)
        {
            this->mat.pixel(y, x) = calc_color(x, y, k_x, k_y, phi_x, phi_y, saturation, value);
        }
    }
}




} // Ende namespace Effects

} // Ende namspace LEDArrangement