var cityname;
var searchresult;
var articlenum = 0;

function getweather(){
   
    $('.name').empty();
    $('.weather').empty();
    $('.temp').empty();
    $('.humidity').empty();
    $('.windspeed').empty();

    cityname = document.getElementById("searchinput2").value;
    //alert("The city you typed is: " + cityname);
    
    $.getJSON("http://api.openweathermap.org/data/2.5/weather?q=" + cityname + "&units=imperial&appid=3d27f58a12f270ae3b0c7e213bf8ce19", 
    function (data){
        console.log(data);

        var icon = "http://openweathermap.org/img/w/" + data.weather[0].icon + ".png";
        console.log(icon); 
        var name = data.name;
        var temp = data.main.temp;
        var weather = data.weather[0].main;
        var humidity = data.main.humidity;
        var windspeed = data.wind.speed;

        $('.icon').attr('src', icon);
        $('.name').append("Location Name: " + name);
        $('.weather').append("Weather: " + weather);
        $('.temp').append("Temperature(F): " + temp);
        $('.humidity').append("Humidity: " + humidity);
        $('.windspeed').append("Wind Speed: " + windspeed + " mph");
        $('.locationhistory').append(name + ",     ");
    }
);    
}

function searchnature(){
    $('.title').empty();
    $('.author').empty();
    $('.publicationname').empty();
    $('.url').empty();
    $('.abstract').empty();
    
    searchresult = document.getElementById("searchinput").value;
    //alert("Searching database for: " + searchresult);

    $.getJSON("http://api.springernature.com/meta/v2/json?q=" + searchresult + "&api_key=1a20e7923c422a5cd262b302857b505e", 
    function (data){
        console.log(data);

        var title = data.records[articlenum].title;
        var author = data.records[articlenum].creators[0].creator;
        var publicationname = data.records[articlenum].publicationName;
        var url = data.records[articlenum].url[0].value;

        $('.title').append("Title: " + title);
        $('.author').append("Author: " + author);
        $('.publicationname').append("Publication Name: " + publicationname);
        $('.url').append("Url: " + url);
    }
    );
}

function nextarticle(){
    if (articlenum < 9)
    {
        articlenum++;
        $('.abstract').empty();
        searchnature();
    } else {
        alert("Maximum number of articles reached");
    }
}

function previousarticle(){
    if (articlenum <= 0)
    {
        alert("Displaying the first result already");
    } else {
        articlenum--;
        $('.abstract').empty();
        searchnature();        
    }
}

function readabstract(){
    $('.abstract').empty();
    searchresult = document.getElementById("searchinput").value;
    $.getJSON("http://api.springernature.com/meta/v2/json?q=" + searchresult + "&api_key=1a20e7923c422a5cd262b302857b505e", 
    function (data){
        console.log(data);

        var abstract = data.records[articlenum].abstract;
        
        $('.abstract').append("Abstract:   " + abstract);
    }
    );
}

