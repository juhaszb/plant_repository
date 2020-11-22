package hu.bme.aut.plantdroid.network

import hu.bme.aut.plantdroid.data.PlantList
import hu.bme.aut.plantdroid.data.SensorList
import retrofit2.Call
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

object PlantsService {
    private var baseUrl = "http://localhost:9999"

    fun setBaseUrl(url: String) {
        baseUrl = url
        api = createApi()
    }

    private var api = createApi()

    private fun createApi(): PlantApi {
        return Retrofit.Builder()
            .baseUrl(baseUrl)
            .addConverterFactory(GsonConverterFactory.create())
            .build()
            .create(PlantApi::class.java)
    }

    fun listPlants(): Call<PlantList> = api.listPlants()

    fun listSensors(): Call<SensorList> = api.listSensors()
}