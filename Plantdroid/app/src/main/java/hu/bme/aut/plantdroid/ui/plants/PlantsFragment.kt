package hu.bme.aut.plantdroid.ui.plants

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.viewModels
import androidx.lifecycle.Observer
import hu.bme.aut.plantdroid.R
import kotlinx.android.synthetic.main.fragment_plants.view.*

class PlantsFragment : Fragment() {

    private val plantsViewModel: PlantsViewModel by viewModels()

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val root = inflater.inflate(R.layout.fragment_plants, container, false)

        val adapter = PlantsAdapter()
        root.plants_recycler_view.adapter = adapter

        plantsViewModel.getPlants().observe(viewLifecycleOwner, Observer {
            adapter.submitList(it)
        })
        plantsViewModel.getMessage().observe(viewLifecycleOwner, Observer {
            Toast.makeText(context, it, Toast.LENGTH_LONG).show()
        })

        return root
    }
}