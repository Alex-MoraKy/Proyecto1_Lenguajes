# Golang 


## Conceptos Fundamentales

### 1. Uso de comandos para controlar el flujo del programa.

El lenguajes de programación Go comparte con muchos del paradigma imperativo la forma que controlan el flujo del programa. En específico usan estass 3 tipos de estructuras básicas:
- if-else: típica condicional de dos vías. Tiene una variante, y es que puede generar un valor si se entra en alguna de las dos vías.
``` go
if v := math.Pow(x, n); v < lim {
		return v
} else {

}
``` 
- for: se usa para iterar (no hay while). Tiene 3 parámetros, una inicialización, una condición de parada, y un aumento. Además, ya que no hay while se puede implementar por medio del for quitando los parámetros de inicialización y aumento. Y en caso de que se desee un while true, se escribe el for solo.
``` go 
for i := 0; i < 10; i++ {
		sum += i
}
```
- switch-case: condicional con más de 2 vías. No permite que la variable a comparar sea un entero y no hace falta poner un break al final del case para que los otros no ocurra.
``` go 
switch dia := semana[3]; dia {
	case "viernes":
		fmt.Println("Ya fin de semana!")
	case "lunes":
		fmt.Println("Apenas Iniciando")
    case "miercoles":
        fmt.Println("Mitad de semana")
	default:
		fmt.Printf("cualquier otro dia")
}  
``` 
- break: para terminar ejecución de un ciclo. 
- continue: continuar a siguiente iteración de un ciclo.
- goto: Es similar al jump de ensamblador, transfiere a ejecución de un programa hacia un label. El ejemplo a continuación solo imprime los números mayores a 20 en un arreglo

``` go 
LABEL: for i := 0; i < len(arr); i++ {

    if arr[i] <= 20 {
        goto LABEL:
    }
    fmt.Printf("menor que 20: "arr[i])
}
```
- fallthrough: lo que hace es pasar la ejecución de un bloque en un case al siguiente menor

``` go 
switch number {
    case 1:
        fmt.Println("uno")
        fallthrough
    case 2:
        fmt.Println("dos")
        fallthrough
    case 3:
        fmt.Println("tres")
    }
```
Si number es 2, entonces imprimiría:

``` bash 
dos 
tres
``` 

### 2. Empleo de asignaciones a variables para manipular el estado del sistema. 

Las variables en go se pueden inicializar en dos lugares dentro de funciones (locales) o bien fuera de funciones (package-level/global).

Existen dos tipos de declaración la standard y la short

#### Standard

Las variables en go se inicializan con la palabra *var* seguido de un identificador (solo un tipo de dato por línea), además usan *=* como signo :

``` go
var nombre string = "Santiago"
var dia, noche bool = true, false
var edad int = 20
```

También se pueden declarar sin poner el tipo y el compilador va a inferir el tipo de dato (permite muchis tipos por línea):

``` go
var nombre, dia = "Santiago", true
var edad, noche = 20, false
```

Además se pueden declarar sin linkear un valor (se ocupa especificar tipo de dato):

``` go
var nombre, apellido string 
var edad, mes int 
```
Finalmente se pueden declarar muchas variables con solo una palabra clave var:

``` go
var ( 
    nombre, edad = "Santiago", 20
    dia, noche bool = true, false
)
```
#### Short

También se usa para asignar variables, pero solo dentro de funciones, además se usa el *:=* como signo y no se usa *var*:
``` go
nombre, apellido := "Santiago", "Chaves"
edad, dia := 20, false
```
cabe recalcar que si se quiere crear una  redeclaración se ocupa usar el *=*, mínimo debe haber una declaración nueva para usar *:=* :

``` go
// se puede
nombre := "Santiago"

// se puede
edad, nombre := 20, "Alex"

// no se puede
nombre := "Santiago"

// se puede
nombre = "Santiago"
```

También si se declaran variables que no se usan, en tiempo se dará un error.


### 3. Forma de definir una ejecución secuencial de instrucciones 

Lo primero que hay que hacer es definir el paquete que se va a ejecutar como main, ya que go funciona con paquetes.
``` go
package main

import "fmt"

func main() {
   fmt.Println("Hola mundo!")
}
```

Ahora bien, dentro del main está el código que será ejecutado línea por línea por go. También se pueden hacer llamadas a funciones lo cual hará que la ejecución se pase a dichas rutinas y al finalizarlas regresará a la ejecución secuencial del main.

## Aspectos de Léxico y Sintaxis

### 1. Sintaxis de forma libre 

#### Tokens
En go existen los tokens, que hacen referencia a palabras que tienen un significado para el compilador. Pueden ser ya sea palabras reservadas, identificadores, una constante, una literal o un simbolo.

``` go
fmt.Println("Hola mundo!")
```
En dicho bloque hay distintos tokens que go detecta: fmt,el punto, Println, los paréntesis, y la string.

#### Salto de línea

En go a diferencia de lenguajes como C o Java, no se ocupa poner un ; al final de una oración, solo basta con usar saltos de línea para cambiar a una nueva instrucción.

#### Comentarios

Se pueden usar estos dos tipos
``` go
// Hola go!
/* 
    Hola 
    go!
*/
```

#### Espacios en Blanco

En go tanto los comentarios o líneas sin contenido son tomados como espacios en blanco. También le da información al compilador sobre donde está ubicados los elementos en una declaración.


### 2. Definiciones

#### Funciones


##### Estructura

Todos los programas en go mínimo tienen la función main, pero se recomienda dividir el código en distintas funciones. Cuando se declara una función se le informa al compilador el tipo de dato que retorno, el identificador y sus parámetros.

Usualmente esta es la estructura básica:

``` go
func nombre( [lista de parametros] ) [tipos de retorno]
{
   cuerpo de la función
}
```


##### llamada

Ya una vez declarada la función el compilador conoce su identificador por lo que solo hace falta mencionarla para llamarla. Al hacer esto se transfiere el control de la ejecución del programa a la función hasta que esta termine y al retornar devuelva el control al main.



``` go
package main

import "fmt"

func main() {
    
    fmt.Println("Dentro del main")

    funcion()
}
func funcion()
{
  fmt.Println("Dentro de la funcion")
}
```

##### Multiples retornos

Una función en go puede retornar múltiples valores de distintos o mismo tipo de la siguiente forma:

``` go
func invertir(x, y string) (string, string) {
   return y, x
}
```

##### Paso de parámetros

Existen dos formas de pasar parámetros en go (por defecto se usa por valor):

- **Por valor**: Copia el valor pasado a la función y los cambios hechos en el interior de la función no afectan al valor original.
- **Por referencia**: Se pasa una referencia (puntero) hacia el parámetro enviado y así poder modificarlo desde dentro de la función. Se usa el * en el parámetro para definir que se quiere pasar por referencia, y en la llamada se usa & acompañado del nombre de la variable a enviar.


##### Tipos de declaración

**Por valor**:

- Se pueden crear dentro de la declaración de a una variable:
``` go
func main(){
   
   raizCuadrada := func(x float64) float64 {
      return math.Sqrt(x)
   }

   fmt.Println(raizCuadrada(9))
}
``` 
- También se puede asignar una función nueva a una variable

``` go
func raizCuadrada(x float64) float64 {
      return math.Sqrt(x)
}
func main(){
   
   raiz := raizCuadrada

   fmt.Println(raiz(9))
}
```
- Pasarla como parámetro a otra función:
``` go
/* la funcion calcular puede  ejecutar cualquier calculo ya que el tipo de calculo se le inyecta. Es un tipo de dependency injection */

func calcular(x int, y int, op func(int, int) int) int {
    return op(x, y)
}

func multiplicar(x int, y int) int {
    return x * y
}

func main() {
    resultado := calcular (2, 5, multiplicar)
    fmt.Println("Resultado:", resultado)
} 
``` 

- Retornada en una función:
``` go
func calcular(factor int) func(int) int {
    return func(valor int) int {
        return factor * valor
    }
}

func main() {
    multiplicarPor2 := calcular(2)
    resultado := multiplicarPor2(20)
    fmt.Println("Resultado:", resultado)
}
```

**Por Closure**:

Este tipo de función es muy única. Ocurre cuando una función puede acceder a los valores de una función que la envuelve. A continuación un ejemplo de un contador que al llamar la variable que almacena la función incrementa a count:

``` go
contador := func() func() int {
	count := 0
	return func() int {
		count++
		return count
	}
}
incrementar := counter()

//incrementa la variable count en 2
incrementar()
incrementar()
``` 

**Por metodo**:

Este tipo es muy común usarlo con structs. Lo que hace es asociar un tipo (structs en su mayoría) con una función usando el operado ".":

``` go
type Rectangulo struct {
    Ancho, Alto float64
}

func (r Rectangulo) Area() float64 {
    return r.Ancho * r.Alto
}


func main(){

    rect := Rectangulo{2, 3}
    // se puede llamar a la función usando el .
    fmt.Println(rect.area())

}
```

#### Tipos de Datos

En go existen los siguientes tipos de datos:

- **Boolean:** consisten en los valores binarios (bool) true y false.
- **Numeric:** son tipos númericos, se subdivide en enteros y flotantes.
- **String:** Es una cadena de bits que representa un set de valores de tipo string. Son inmutables.
- **Derived:** Incluyen punteros, arreglos, estructuras, uniones, funciones, slices, interfaces, maps, y canales.

### 3. Tipos de datos básicos

#### Enteros

Los enteros son una subdivición de los tipos de datos numéricos. Golang ofrece divisiones por si el entero tiene signo o no, o bien para diferentes tamaños:

| Numero | Tipos   | Descripción                                      |
|--------|---------|--------------------------------------------------|
| 1      | uint8   | Unsigned 8-bit integers (0 to 255)               |
| 2      | uint16  | Unsigned 16-bit integers (0 to 65535)            |
| 3      | uint32  | Unsigned 32-bit integers (0 to 4294967295)       |
| 4      | uint64  | Unsigned 64-bit integers (0 to 18446744073709551615) |
| 5      | int8    | Signed 8-bit integers (-128 to 127)              |
| 6      | int16   | Signed 16-bit integers (-32768 to 32767)         |
| 7      | int32   | Signed 32-bit integers (-2147483648 to 2147483647) |
| 8      | int64   | Signed 64-bit integers (-9223372036854775808 to 9223372036854775807) |

Dependiendo de la arquitectura en la que se esté se usará por defecto el de 32 o 64 bits.

#### Punto Flotantes

Los enteros son una subdivición de los tipos de datos numéricos. Golang ofrece divisiones por si el entero tiene signo o no, o bien para diferentes tamaños:

| Numero | Tipos   | Descripción                                      |
|--------|---------|--------------------------------------------------|
| 1      | float32 | Números punto flotante de IEEE-754 32-bit        |
| 2      | float64 | Números punto flotante de IEEE-754 64-bit        |
| 3      | complex64 | Números complejos con float32 real y para imaginaria  |
| 4      | complex128 | Números complejos con float64 real y para imaginaria |

#### Void

En go no existe la palabra reservada void, en caso no desear un retorno simplemente se omite el tipo de dato.

### 4. Declaraciones e identificadores

#### Uso de palabras clave, como static, extern, typedef

##### Static
En go no se usa static, y si se desea que una función sea accesible desde otros paquetes se usan los nombres de la función en mayúscula en su primera letra.


##### extern 

Para importar funciones o paquetes externos se usa la palabra import.

##### Typedef

En go si se le quiere dar un alias a un tipo de dato se puede usar *type*, esto permite hacer la misma función que el typedef en C.


#### Identificadores

Se usan para darle nombres únicos a funciones, variables, constantes o tipos. En GO los identificadores pueden saber si contenido es mayúscula o minúscula, por ello VAR != var. Además, estas son las reglas básicas:
- Solo pueden contener letras, digitos, o barras bajas.
- Deben iniciar en letras o barras bajas.
- No pueden contener espacios o carácteres especiales.
- No pueden ser iguales a las palabras reservadas de Go.

#### Variables Globales y Locales

Ya previamente se comentó sobre ellas y sus usos con *:=* o *=*. Ahora bien, con respecto a sus diferencias, como en muchos lenguajes como C, si hay diferencia las principales son:
- Las globales se declaran fuera de todas las funciones, mientras las locales son específicas a un scope.
- Las globales se declaran en el heap, y las locales en el stack.
- Las locales solo existen durante la ejecución del scope, y las globales durante todo el programa
- Los scopes superiores son agnósticos a las declaraciones locales de sus scopes "hijos".
