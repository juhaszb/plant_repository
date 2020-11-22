package hu.bme.aut.plantdroid.ui.sensors

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.viewModels
import androidx.lifecycle.Observer
import hu.bme.aut.plantdroid.R
import kotlinx.android.synthetic.main.fragment_sensors.view.*

class SensorsFragment : Fragment() {

    private val sensorsViewModel: SensorsViewModel by viewModels()

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val root = inflater.inflate(R.layout.fragment_sensors, container, false)

        val adapter = SensorsAdapter()
        root.sensors_recycler_view.adapter = adapter

        sensorsViewModel.getSensors().observe(viewLifecycleOwner, Observer {
            adapter.submitList(it)
        })
        sensorsViewModel.getMessage().observe(viewLifecycleOwner, Observer {
            Toast.makeText(context, it, Toast.LENGTH_LONG).show()
        })

        return root
    }
}