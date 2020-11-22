package hu.bme.aut.plantdroid.ui.sensors

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import hu.bme.aut.plantdroid.data.Sensor
import hu.bme.aut.plantdroid.data.SensorList
import hu.bme.aut.plantdroid.network.PlantsService
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class SensorsViewModel : ViewModel() {
    private val sensors: MutableLiveData<List<Sensor>> by lazy {
        MutableLiveData<List<Sensor>>().also {
            loadSensors()
        }
    }

    fun getSensors(): LiveData<List<Sensor>> = sensors

    private val message = MutableLiveData<String>()

    fun getMessage(): LiveData<String> = message

    private fun loadSensors() {
        PlantsService.listSensors().enqueue(object : Callback<SensorList> {
            override fun onFailure(call: Call<SensorList>, t: Throwable) {
                message.value = t.message
            }

            override fun onResponse(call: Call<SensorList>, response: Response<SensorList>) {
                if (response.isSuccessful)
                    sensors.value = response.body()?.sensors
                else
                    message.value = "${response.code()}: ${response.message()}"
            }

        })
    }
}