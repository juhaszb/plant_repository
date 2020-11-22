package hu.bme.aut.plantdroid.ui.sensors

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import hu.bme.aut.plantdroid.R
import hu.bme.aut.plantdroid.data.Sensor
import kotlinx.android.synthetic.main.sensor_item.view.*

class SensorsAdapter : ListAdapter<Sensor, SensorsAdapter.SensorViewHolder>(SensorDiffCallback) {
    class SensorViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        fun bind(sensor: Sensor) {
            itemView.sensor_id.text = sensor.id.toString()
            itemView.sensor_name.text = sensor.name
            itemView.sensor_data.text = sensor.data.toString()
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): SensorViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.sensor_item, parent, false)
        return SensorViewHolder(view)
    }

    override fun onBindViewHolder(holder: SensorViewHolder, position: Int) {
        val sensor = getItem(position)
        holder.bind(sensor)
    }
}

object SensorDiffCallback : DiffUtil.ItemCallback<Sensor>() {
    override fun areItemsTheSame(oldItem: Sensor, newItem: Sensor) = oldItem == newItem

    override fun areContentsTheSame(oldItem: Sensor, newItem: Sensor) = oldItem == newItem
}