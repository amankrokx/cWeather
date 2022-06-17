const express = require("express")
const bodyParser = require("body-parser")
const fetch = require("node-fetch")
const { response } = require("express")

// creating of express app
const app = express()

// enabling CROS
app.use(function (req, res, next) {
    res.header("Access-Control-Allow-Origin", "http://localhost:3069") // update to match the domain you will make the request from
    res.header("Access-Control-Allow-Methods", "GET,POST")
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept")
    res.header("Access-Control-Allow-Credentials", "true")
    next()
})
// use body parser to decode query params and json body.
app.use(
    bodyParser.urlencoded({
        extended: true,
    })
)
app.use(express.json())

// port set-up
const port = process.env.PORT || 6969 // Unique port not to conflict...

let getWeather = (lat, lon) => {
    return new Promise((resolve, reject) => {
        let url = `https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&appid=b1741d4b9a702da375fddc8571ba4eaa`
        fetch(url)
            .then(response => response.json())
            .then(json => {
                // console.log(json)
                // Start extracting data
                let j = json.main
                let wa = [json.weather[0].main, json.weather[0].description, json.base, j.temp, j.feels_like, j.pressure, j.humidity, json.wind.speed, json.wind.deg, json.name]
                let wstr = wa.join(",")
                resolve(wstr)
            })
            .catch(err => {
                console.error("error:" + err)
                reject(err)
            })
    })
}

// API's
app.get("/", (req, res) => {
    if (req.query) {
        if (req.query.lat && req.query.lon) {
            // console.log(req.query)
            getWeather(req.query.lat, req.query.lon)
                .then(data => res.send(data))
                .catch(err => res.status(400).send(err))
        } else if (req.query.address) {
            // console.log(req.query)
            let address = encodeURIComponent(req.query.address)
            const url = `https://google-maps-geocoding.p.rapidapi.com/geocode/json?address=${address}&language=en`

            const options = {
                method: "GET",
                headers: {
                    "X-RapidAPI-Key": "15be109401msh039dc334993a18cp1b9113jsn7f88dd5900bf",
                    "X-RapidAPI-Host": "google-maps-geocoding.p.rapidapi.com",
                },
            }

            fetch(url, options)
                .then(response => response.json())
                .then(json => {
                    // res.json(json)
                    // get lat and lon
                    if (json.status === "OK") {
                        let ta = [json.results[0].geometry.location.lat, json.results[0].geometry.location.lng, json.results[0].formatted_address]
                        let tstr = ta.join(",")
                        getWeather(ta[0], ta[1])
                            .then(data => res.send(data + tstr))
                            .catch(err => res.status(400).send(err))
                    }
                })
                .catch(err => {
                    res.status(400).send(err)
                    console.error("error:" + err)
                })
        } else {
            let ip = req.headers["x-forwarded-for"] || req.socket.remoteAddress // ip address of remote client
            const url = "https://ip-geolocation-and-threat-detection.p.rapidapi.com/" + ip

            const options = {
                method: "GET",
                headers: {
                    "X-RapidAPI-Key": "15be109401msh039dc334993a18cp1b9113jsn7f88dd5900bf",
                    "X-RapidAPI-Host": "ip-geolocation-and-threat-detection.p.rapidapi.com",
                },
            }

            fetch(url, options)
                .then(response => response.json())
                .then(json => {
                    // console.log(json.location)
                    let ta = [json.location.latitude, json.location.longitude, json.location.city, json.location.postal, json.location.region.name, json.location.country.name]
                    let tstr = ta.join(",")
                    getWeather(ta[0], ta[1])
                        .then(data => res.send(data + tstr))
                        .catch(err => res.status(400).send(err))
                    // res.json(json)
                })
                .catch(err => {
                    res.status(400).send(err)
                    console.error("error:" + err)
                })
        }
    }
})

// server listening
app.listen(port, () => {
    console.log(`server is running at port ${port}`)
})
