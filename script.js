const semana = [
  {
    nombre: "Domingo",
    actividades: [
      { nombre: "Descansar", inicio: 10, fin: 12, realizada: false },
      { nombre: "Series", inicio: 18, fin: 20, realizada: false }
    ]
  },
  {
    nombre: "Jueves",
    actividades: [
      { nombre: "goldemessi", inicio: 0, fin: 2, realizada: false },
      { nombre: "Entrenar", inicio: 8, fin: 9, realizada: false },
      { nombre: "Comer", inicio: 13, fin: 14, realizada: false },
      { nombre: "Dormir", inicio: 23, fin: 24, realizada: false }
    ]
  }
];
function cargarActividades(){
const dias = ["Domingo","Lunes","Martes","Miércoles","Jueves","Viernes","Sábado"];

const ahora = new Date();
const nombreDia = dias[ahora.getDay()];

const diaActual = semana.find(d => d.nombre === nombreDia);

// fallback por seguridad
const actividades = diaActual ? diaActual.actividades : [];

document.getElementById("dia").innerText = nombreDia;

document.getElementById("hora").innerText =
  ahora.getHours().toString().padStart(2,"0") + ":" +
  ahora.getMinutes().toString().padStart(2,"0");

const contenedor = document.getElementById("actividades");

actividades.forEach((a,i)=>{
  contenedor.innerHTML += `
    <div class="actividad">
      <input type="checkbox" id="act${i}">
      ${a.nombre}
      (${a.inicio}:00 - ${a.fin}:00)
    </div>
  `;
});
}
let horasPendientes = 0;

function generarCronograma(){

  let horaActual = ahora.getHours();
  horasPendientes = 0;
  let salida = "";

  actividades.forEach((a,i)=>{

    a.realizada = document.getElementById(`act${i}`).checked;

    if(!a.realizada){

      let duracion = a.fin - a.inicio;

      salida += `${horaActual}:00 - ${horaActual + duracion}:00 -> ${a.nombre}\n`;

      horaActual += duracion;
      horasPendientes += duracion;
    }
  });

  document.getElementById("cronograma").innerText = salida;
}

function evaluarActividad(){

  const nombre = document.getElementById("nombreActividad").value;

  const duracion = parseInt(document.getElementById("duracionActividad").value);

  const horaActual = ahora.getHours();

  const libres = (24 - horaActual) - horasPendientes;

  if(duracion <= libres){
    document.getElementById("resultado").innerText =
      `✅ Sí podés hacer ${nombre}. Te quedan ${libres - duracion} horas libres.`;
  } else {
    document.getElementById("resultado").innerText =
      `❌ No podés hacer ${nombre}. Solo tenés ${libres} horas libres.`;
  }
}