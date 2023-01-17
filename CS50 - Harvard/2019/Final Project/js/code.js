function login() {
    
    email = document.getElementById('formulario').elements[0].value,
    password = document.getElementById('formulario').elements[1].value
    firebase
        .auth()
        .signInWithEmailAndPassword(email, password)
        .then(data => {
            var uid = data.user.uid
            window.location.href = ("../html/table.html")
        })
        .catch(function(error) {
            console.error(error.code)
            console.error(error.message)
            alert(error.message)
        })
    document.getElementById("formulario").reset()
}
function logout() {
    firebase
    .auth()
    .signOut()
    .then(function () {
        window.location.href = ("../html/principal.html")
    })
    .catch(function(error) {
        console.error(error.code)
        console.error(error.message)
        alert(error.message)
    })
}

function register() {
    email = document.getElementById('formulario').elements[0].value
    password = document.getElementById('formulario').elements[1].value
    confirmation = document.getElementById('formulario').elements[2].value
    if ( password != confirmation ){
        return window.alert("Your passwrods don't match!")
    }
    if ( password.length < 5) {
        return window.alert("Your inputs have to have at least 6 characters!")
    }
    var database = firebase.database()
    var ref = database.ref('userinfo')
    firebase
        .auth()
        .createUserWithEmailAndPassword(email, password)
        .then( data => {
            alert("Registered!")
            window.location.href = ("../html/table.html")
        })
        .catch(function(error) {
            console.error(error.code)
            alert(error.message)
        })
    document.getElementById("formulario").reset()
}

function checkbox() {
    var checkboxCash = document.getElementById("cash")
    var checkboxSpent = document.getElementById("spent")
    checkboxCash.addEventListener("click", function(){
        if (checkboxSpent.checked) {
            
            console.log("spent = false")
            return checkboxSpent = false
        }
    })
    checkboxSpent.addEventListener("click", function(){
        if (checkboxCash.checked) {
            console.log("cash = flase")
            return checkboxCash = false
        }
    })
}
function displayTable () {
    firebase.auth().onAuthStateChanged(function(user) {
        if (user) {
            uid = firebase.auth().currentUser.uid
            var database = firebase.database()
            var ref = database.ref(`userinfo/` + uid)

            var totalCash = database.ref('userinfo/' + uid)

            ref.once('value', function(snapshot) {
                var info = snapshot.val()
                var keys = Object.keys(info)
                
                for (var i = 0 ; i < keys.length ; i++) {
                    var k = keys[i]
                    var tabela = document.getElementById("tabela")
                    var length = tabela.rows.length
                    
                    
                    var datac = new Date()
                    var mm = Number(datac.getMonth() + 1)
                    console.log(mm)
                    if (info[k].Purpose != undefined){

                        var m = (info[k].Date[3] + info[k].Date[4])
                        console.log(m)
                        if (  mm == m) {
                            var linha = tabela.insertRow(1)
                            var cellPurpose = linha.insertCell(0)
                            var cellPrice = linha.insertCell(1)
                            var cellType = linha.insertCell(2)
                            var cellDate = linha.insertCell(3)
                            cellPurpose.innerHTML = info[k].Purpose
                            cellPrice.innerHTML = `US$ ${info[k].Price}`
                            cellType.innerHTML = info[k].Type
                            cellDate.innerHTML = info[k].Date
                        }
                        
                    }
                    
                }

                var database = firebase.database()

                var tSpent = database.ref('userinfo/' + uid).child("Spent")
                var tCash = database.ref('userinfo/' + uid).child("Cash")
                
                tCash.once('value', function(snapshot) {
                    var infoC = Number(snapshot.val())
                    tSpent.once('value', function(snapshot) {
                        var infoS = Number(snapshot.val())

                        var totalCash = document.getElementById("totalcash")
                        var totalSpent = document.getElementById("totalspent")

                        totalCash.innerHTML = `Total Cash: US$${infoC}`
                        totalSpent.innerHTML = `Total Spent: US$${infoS}`
                    })
                })
            })
        } else {
          console.log("Error")
        }
        
      });
}

function addNew() {
    var purpose = document.getElementById("purpose").value
    var price = document.getElementById("price").value
    var date = document.getElementById("date").value
    var checkboxCash = document.getElementById("cash").checked
    
    var checkboxSpent = document.getElementById("spent").checked
    
    var type
    if (!checkboxCash && !checkboxSpent){
        return alert("You must check one checkbox (Cash or Spent)")
    }
    var uid
    firebase.auth().onAuthStateChanged(function(user) {
        if (user) {
            uid = firebase.auth().currentUser.uid
            var type
            

            if (checkboxCash) {
                type = "Cash"
                var addCash = Number(price)
                var database = firebase.database()
                var totalCash = database.ref('userinfo/' + uid).child("Cash")

                totalCash.once('value', function(snapshot) {
                    var info = Number(snapshot.val())

                    addCash += info
                   
                    firebase.database()
                        .ref('userinfo/' + uid)
                        .child("Cash")
                        .set(addCash)

                        var d = date[8] + date[9] + "/" + date[5] +  date[6] + "/" + date[0] + date[1] + date[2] + date[3]
        

                        var new_data = {
                            Purpose: purpose,
                            Price: price,
                            Type: type,
                            Date: d
                        }
                        firebase.database()
                            .ref('/userinfo/')
                            .child(uid)
                            .push(new_data)
                        
                        var tabela = document.getElementById("tabela")
                        var length = tabela.rows.length
                        var linha = tabela.insertRow(1)
            
                        var cellPurpose = linha.insertCell(0)
                        var cellPrice = linha.insertCell(1)
                        var cellType = linha.insertCell(2)
                        var cellDate = linha.insertCell(3)
            
                        cellPurpose.innerHTML = purpose
                        cellPrice.innerHTML = `US$ ${price}`
                        cellType.innerHTML = type
                        cellDate.innerHTML = d
            
                        var totalCash = document.getElementById("totalcash")
        
                        totalCash.innerHTML = `Total Cash: US$${addCash}`
                })
                
            }
            else {
                type = "Spent"
                var database = firebase.database()
                var totalSpent = database.ref('userinfo/' + uid).child("Spent")
                var addSpent = Number(price)
                
                var tCash = database.ref('userinfo/' + uid).child("Cash")
                var totalCash = database.ref('userinfo/' + uid).child("Cash")
                var infoC
                totalCash.once('value', function(snapshot) {
                    infoC = Number(snapshot.val())
                    totalSpent.once('value', function(snapshot) {
                    var infoS = Number(snapshot.val())
                    console.log(infoC)
                    console.log(addSpent)
                    infoC -= addSpent
                    if (infoC < 0) {
                        return alert("You don't have enough cash!")
                    }
                    else {
                        addSpent += infoS

                        firebase.database()
                            .ref('userinfo/' + uid)
                            .child("Cash")
                            .set(infoC)
                        firebase.database()
                            .ref('userinfo/' + uid)
                            .child("Spent")
                            .set(addSpent)

                        var d = date[8] + date[9] + "/" + date[5] +  date[6] + "/" + date[0] + date[1] + date[2] + date[3]
        

                        var new_data = {
                            Purpose: purpose,
                            Price: price,
                            Type: type,
                            Date: d
                        }
                        firebase.database()
                            .ref('/userinfo/')
                            .child(uid)
                            .push(new_data)
                        
                        var tabela = document.getElementById("tabela")
                        var length = tabela.rows.length
                        var linha = tabela.insertRow(1)
            
                        var cellPurpose = linha.insertCell(0)
                        var cellPrice = linha.insertCell(1)
                        var cellType = linha.insertCell(2)
                        var cellDate = linha.insertCell(3)
            
                        cellPurpose.innerHTML = purpose
                        cellPrice.innerHTML = `US$ ${price}`
                        cellType.innerHTML = type
                        cellDate.innerHTML = d
            
                        var totalCash = document.getElementById("totalcash")
                        var totalSpent = document.getElementById("totalspent")

                        totalCash.innerHTML = `Total Cash: US$${infoC}`
                        totalSpent.innerHTML = `Total Spent: US$${addSpent}`



                    }
                })
                })
                
            }

           
        } else {
          console.log("Error")
        }
      })
}  

function loadhistory() {
    firebase.auth().onAuthStateChanged(function(user) {
        if (user) {
            uid = firebase.auth().currentUser.uid
            var database = firebase.database()
            var ref = database.ref(`userinfo/` + uid)

            var totalCash = database.ref('userinfo/' + uid)

            ref.once('value', function(snapshot) {
                var info = snapshot.val()
                var keys = Object.keys(info)
                
                for (var i = 0 ; i < keys.length ; i++) {
                    var k = keys[i]
                    var tabela = document.getElementById("tabela")
                    var length = tabela.rows.length
                    
                    if (info[k].Purpose != undefined){
                            var linha = tabela.insertRow(1)

                            var button = document.createElement("input")
                            button.type = "button"
                            button.value = "Delete"


                            var cellPurpose = linha.insertCell(0)
                            var cellPrice = linha.insertCell(1)
                            var cellType = linha.insertCell(2)
                            var cellDate = linha.insertCell(3)

                            cellPurpose.innerHTML = info[k].Purpose
                            cellPrice.innerHTML = `US$ ${info[k].Price}`
                            cellType.innerHTML = info[k].Type
                            cellDate.innerHTML = info[k].Date 
                    }
                    
                }
            })
        }
        else {
            console.log("Error")
        }
    })
        
} 

