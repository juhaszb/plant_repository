package hu.bme.aut.plantdroid.ui.plants

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import hu.bme.aut.plantdroid.R
import hu.bme.aut.plantdroid.data.Plant
import kotlinx.android.synthetic.main.plant_item.view.*

class PlantsAdapter : ListAdapter<Plant, PlantsAdapter.PlantViewHolder>(PlantDiffCallback) {
    class PlantViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        fun bind(plant: Plant) {
            itemView.plant_id.text = plant.id.toString()
            itemView.plant_name.text = plant.name
            itemView.plant_gridx.text = plant.gridX.toString()
            itemView.plant_gridy.text = plant.gridY.toString()
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PlantViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.plant_item, parent, false)
        return PlantViewHolder(view)
    }

    override fun onBindViewHolder(holder: PlantViewHolder, position: Int) {
        val plant = getItem(position)
        holder.bind(plant)
    }
}

object PlantDiffCallback : DiffUtil.ItemCallback<Plant>() {
    override fun areItemsTheSame(oldItem: Plant, newItem: Plant) = oldItem == newItem

    override fun areContentsTheSame(oldItem: Plant, newItem: Plant) = oldItem == newItem
}