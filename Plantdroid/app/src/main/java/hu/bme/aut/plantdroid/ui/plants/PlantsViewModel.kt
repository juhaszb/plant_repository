package hu.bme.aut.plantdroid.ui.plants

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import hu.bme.aut.plantdroid.data.Plant
import hu.bme.aut.plantdroid.data.PlantList
import hu.bme.aut.plantdroid.network.PlantsService
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class PlantsViewModel : ViewModel() {
    private val plants: MutableLiveData<List<Plant>> by lazy {
        MutableLiveData<List<Plant>>().also {
            loadPlants()
        }
    }

    fun getPlants(): LiveData<List<Plant>> = plants

    private val message = MutableLiveData<String>()

    fun getMessage(): LiveData<String> = message

    private fun loadPlants() {
        PlantsService.listPlants().enqueue(object : Callback<PlantList> {
            override fun onFailure(call: Call<PlantList>, t: Throwable) {
                message.value = t.message
            }

            override fun onResponse(call: Call<PlantList>, response: Response<PlantList>) {
                if (response.isSuccessful)
                    plants.value = response.body()?.plants
                else
                    message.value = "${response.code()}: ${response.message()}"
            }

        })
    }
}