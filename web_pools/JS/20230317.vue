<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Vue-Test</title>
    <script src="https://cdn.staticfile.org/vue/2.4.2/vue.min.js"></script>
</head>
<body>

<div id="vue_det">
    <h3>site : {{site}}</h3>
    <h3>url : {{url}}</h3>
    <h3>{{details()}}</h3>
</div>

<div id="app">
    <label for="r1"> change color</label>
    <input type="button" v-model="use" id="r1">
    <p v-if="seen"> now you can look at me</p>

    <p> {{message}}</p>
    <button @click="reverse_message"> reverse message</button>

    <div v-if="Math.random() > 0.5"> random number is larger than 0.5</div>
    <div v-else> number < 0.5</div>

    <ol>
        <li v-for="site in sites">
            {{site.name}}
        </li>
    </ol>

    <ul>
        <li v-for="n in 3">
            {{n}}
        </li>
    </ul>
    <p> origin string:{{strs}}</p>
    <p> computed reverse str:{{rev_strs}} </p>

    <p style="font-size: 25px;"> counter: {{counter}} </p>
    <button @click="CounterIncrease" style="font-size: 25px;"> press me</button>
    <div v-bind:style="{color: activeColor, fontSize: fontSize+'px'}" > Jacky-Div</div>

    <button v-on:click="say('hi')"> Say Hi</button>
</div>

<script type="text/javascript">
    var vm = new Vue({
        el: '#vue_det',
        data: {
            site: "Jacky-Web",
            url: "www.runoob.com",
            alexa: "10000",
            message: "fhj-vue-message",
            use: false
        },
        methods: {
            details: function() {
                return  this.site + " - 想笑！";
            },
            reverse_message: function () {
                this.message = this.message.split('').reverse().join('')
            }
        }
    })

    var app = new Vue({
        el: '#app',
        data: {
            message: "fhj-vue-message",
            seen: false,
            use: false,
            sites:[
                {name: "Jacky"},
                {name: "Fan"},
                {name: "123"},
            ],
            strs: "origin-str",
            counter: 0,
            activeColor: 'red',
            fontSize: 30,
        },
        methods: {
            reverse_message: function () {
                this.message = this.message.split('').reverse().join('')
            },
            CounterIncrease: function () {
                this.counter++
            },
            say: function (message) {
                alert(message)
            }
        },
        computed: {
            rev_strs: function () {
                return this.strs.split('').reverse().join('')
            }
        }
    })
    app.$watch('counter', function (nval, oval){
        alert("counter old:"+oval + " new:"+nval)
    })

</script>
</body>
</html>