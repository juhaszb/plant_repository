package hu.bme.aut.plantdroid.network

import hu.bme.aut.plantdroid.data.Plant
import hu.bme.aut.plantdroid.data.PlantList
import hu.bme.aut.plantdroid.data.Sensor
import hu.bme.aut.plantdroid.data.SensorList
import retrofit2.Call
import retrofit2.http.GET

interface PlantApi {
    @GET("list_plants")
    fun listPlants(): Call<PlantList>

    @GET("list_sensors")
    fun listSensors(): Call<SensorList>
}