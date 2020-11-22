package hu.bme.aut.plantdroid.ui

import android.os.Bundle
import androidx.preference.PreferenceFragmentCompat
import hu.bme.aut.plantdroid.R

class PreferencesFragment : PreferenceFragmentCompat() {
    override fun onCreatePreferences(savedInstanceState: Bundle?, rootKey: String?) {
        setPreferencesFromResource(R.xml.preferences, rootKey)
    }
}