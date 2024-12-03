# Algoritmos II final

¿Qué hace un algoritmo?  
    -> Lo que devuelve

¿Cómo hace el algoritmo?  
    -> Comportamiento interno
  
Analizar el “cómo” permite:  

- Predecir el tiempo de ejecución (eficiencia en tiempo)
- Predecir el uso de memoria (eficiencia en espacio)
- Predecir el uso de otros recursos
- Comparar distintos algoritmos para un mismo problema

## Swap

```cs
{Pre: a = A ∧ 1 ≤ i, j ≤ n} 
proc swap (in/out a: array[1..n] of T, in i, j: nat) 
  var tmp: T 
  tmp  := a[i] 
  a[i] := a[j] 
  a[j] := tmp 
end proc 
{Post: a[i] = A[j] ∧ a[j] = A[i] ∧ ∀ k. k ̸∈{i, j} ⇒ a[k]=A[k]}
```

## Selection Sort

- selecciona el menor de todos los elementos, lo intercambia con el elemento que se encuentra en la primera posición.
- selecciona el menor de todos los restantes, lo intercambia con el que se encuentra en el segundo lugar.
- selecciona el menor de todos los restantes, lo intercambia con en el que se encuentra en el tercer lugar.
- ... (en cada uno de estos pasos ordena un elemento) ...
- hasta terminar.

Invariante:

- el arreglo `a` es una permutación del original,
- un segmento inicial `a[1, i)` del arreglo está ordenado, y
- dicho segmento contiene los elementos mínimos del arreglo.

### Algoritmo Selection Sort

```cs
{Pre: n ≥ 0 ∧ a = A} 
proc selection_sort (in/out a: array[1..n] of T) 
  var i, minp: nat 
  i := 1 
  /* {Inv: Invariante de recién} */ 
  do i < n → 
    minp := min_pos_from(a,i)
    swap(a, i, minp) 
    i := i + 1 
  od 
end proc 
{Post: a está ordenado y es permutación de A}
```

#### Selección

Invariante:

- invariante anterior, y el mínimo del segmento `a[i, j)` está en la posición minp.

```cs
{Pre: 0 < i ≤ n} 
fun min_pos_from (a: array[1..n] of T, i: nat) ret minp: nat 
  var j: nat 
  minp := i 
  j := i + 1 
  /* {Inv: a[minp] es el mínimo de a[i, j)} */ 
  do j ≤ n → 
    if a[j] < a[minp] then 
      minp := j 
    fi 
    j := j + 1 
  od 
end fun 
{Post: a[minp] es el mínimo de a[i, n]}
```

## Numero de operaciones de un programa

Una vez que uno sabe qué operación quiere contar,
Se debe imaginar una ejecución arbitraria, genérica del programa,
Intentando contar el número de veces que esa ejecución arbitraria realizará dicha operación.

Para contar cuántas veces se ejecuta la operación,
entonces, se cuenta cuántas veces se ejecuta cada comando

El comando **skip** equivale a una secuencia vacía:

- `ops(skip) = 0`

El comando **for k:= n to m do C(k) od** “equivale” también a una secuencia:

- $ ops\left(for \, k := n \, to \, m \, do \, C(k) \, od\right) = \sum_{k=n}^m ops(C(k)) $

## Insertion Sort

Invariante:

- el arreglo a es una permutación del original
- un segmento inicial `a[1, i)` del arreglo está ordenado.
- en general `a[1, i)` no contiene los mínimos del arreglo

### Algoritmo Insertion Sort

```cs
{Pre: n ≥ 0 ∧ a = A}
proc insertion_sort (in/out a: array[1..n] of T)
  for i := 2 to n do 
    //  {Inv: Invariante de recién}
    insert(a, i)
  od
end proc
{Post: a está ordenado y es permutación de A}
```

#### Inserción

Invariante:

- el arreglo a es una permutación del original
- `a[1, i]` sin celda j está ordenado
- `a[j, i]` también está ordenado.

```cs
{Pre: 0 < i ≤ n ∧ a = A}
proc insert (in/out a: array[1..n] of T, in i: nat)
  var j: nat
  j := i 
  //  {Inv: Invariante de recién}
  do (j > 1 ∧ a[j] < a[j − 1]) → swap(a, j - 1, j)
    j := j - 1
  od
end proc
{Post: a[1,i] está ordenado ∧ a es permutación de A}
```

## Merge Sort

```cs
{Pre: n ≥ rgt ≥ lft > 0 ∧ a = A}
proc merge_sort_rec (in/out a: array[1..n] of T, in lft, rgt: nat)
  var mid: nat

  //  si el subarray tiene más de un elemento
  if rgt > lft → 
    //  se calcula el punto medio
    mid := (rgt + lft) ÷ 2

    //  se ordena la mitad izquierda
    merge_sort_rec(a, lft, mid)
    
    //  se ordena la mitad derecha
    merge_sort_rec(a, mid + 1, rgt)

    //  se combinan las dos mitades ordenadas
    merge(a, lft, mid, rgt)
  fi
end proc
{Post: a permutación de A ∧ a[lft,rgt] permutación ordenada de A[lft, rgt]}
```

```cs
proc merge_sort (in/out a: array[1..n] of T)
  //  se inicia la llamada recursiva en todo el array
  merge_sort_rec(a, 1, n)
end proc
```

### Merging

```cs
proc merge (in/out a: array[1..n] of T, in lft,mid,rgt: nat)
  //  arreglo temporal para guardar la primera mitad del arreglo  
  var tmp: array[1..n] of T
  j, k: nat

  //  se copia la mitad izquierda de `a` en `tmp`
  for i := lft to mid do tmp[i] := a[i] od
  
  //  se inicializan los punteros, 
  //  `j` para `tmp` que va desde lft hasta mid,
  //  `k` para `a` que va deslde mid + 1 hasta rgt
  j := lft
  k := mid + 1
  
  //  se combinan las dos partes en `a`
  for i := lft to rgt do 
    //  si todavía hay elementos en `tmp`, y
    //  1. ya no hay elementos disponibles en `a`, o
    //  2. el elemento apuntado en `tmp` es menor que el apuntado en `a`
    if j ≤ mid ∧ (k > rgt ∨ tmp[j] ≤ a[k]) then
      //  se copia el elemento apuntado en `tmp` a la posición `i` de `a`
      a[i] := tmp[j]
      j := j + 1
    
    else a[i]:= a[k]
      //  se copia el elemento apuntado en `a` a la posición `i` de `a`
      k := k + 1
    fi
  od
end proc
```

## Quicksort

```cs
{Pre: 0 ≤ rgt ≤ n ∧ 1 ≤ lft ≤ n + 1 ∧ lft - 1 ≤ rgt ∧ a = A}
proc quick_sort_rec (in/out a: array[1..n] of T, in lft, rgt: nat)
  var ppiv: nat
  //  si el subarray tiene más de un elemento
  if rgt > lft → 
    /**
     * se selecciona un pivot, tal que lft ≤ ppiv ≤ rgt
     *
     * se separan los elementos alrededor del pivot
     * tal que:
     * 
     * elementos en a[lft, ppiv - 1] ≤ a[ppiv]
     * elementos en a[ppiv + 1, rgt] ≥ a[ppiv]
     */
    partition(a, lft, rgt, ppiv)

    //  se ordenan las dos mitades del arreglo
    quick_sort_rec(a, lft, ppiv - 1)
    quick_sort_rec(a, ppiv + 1, rgt)
  fi
end proc
{Post: a permut de A ∧ a[lft, rgt] permut ordenada de A[lft, rgt]}
```

```cs
proc quick_sort (in/out a: array[1..n] of T)
  //  se inicia la llamada recursiva en todo el array
  quick_sort_rec(a, 1, n)
end proc
```

### Partition

Invariante:

- lft = piv < i ≤ j + 1 ≤ rgt + 1
- todos los elementos en a[lft,i) son ≤ que a[piv]
- todos los elementos en a(j, rgt] son > que a[piv]

```cs
{Pre: 1 ≤ lft < rgt ≤ n ∧ a = A}
proc partition (in/out a: array[1..n] of T, in lft, rgt: nat, out ppiv: nat)
  var i, j: nat

  //  se selecciona el primer elemento como pivot
  ppiv := lft
  //  se inicializa el puntero izquierdo en el siguiente elemento
  i := lft + 1
  //  se inicializa el puntero derecho en el último elemento
  j := rgt

  //  se separan los elementos alrededor del pivot
  do i ≤ j → 
    
    if 
      //  se dejan los elementos menores al pivot a la izquierda
      a[i] ≤ a[ppiv] → 
        i := i + 1
      
      //  se dejan los elementos mayores al pivot a la derecha
      a[j] ≥ a[ppiv] → 
        j := j - 1

      //  se intercambian los elementos en el lado equivocado del pivot
      a[i] > a[ppiv] ∧ a[j] < a[ppiv] → 
        swap(a, i, j)
        i := i + 1
        j := j - 1

    fi
  od

  //  se deja al pivot en su posición ordenada
  swap(a, ppiv, j)  // {dejando el pivot en una posición más central}
  ppiv := j         //  {señalando la nueva posición del pivot }
end proc
{Post: a[1, lft) = A[1, lft) ∧ a(rgt, n] = A(rgt, n] 
∧ a[lft, rgt] permutación de A[lft, rgt] ∧ lft ≤ piv ≤ rgt
∧ los elementos de a[lft, piv] son ≤ que a[piv]
∧ los elementos de a(piv, rgt] son > que a[piv]}
```

## DyV

El paradigma divide y vencerás, está basado en buscar la resolución recursiva de un problema
dividiéndolo en dos o más subproblemas de igual tipo o similar (sin que se solapen).
El proceso continúa hasta que éstos llegan a ser lo suficientemente sencillos
como para que se resuelvan directamente.
Al final, las soluciones a cada uno de los subproblemas se combinan
para dar una solución al problema original.

### Recurrencia

Una relación de recurrencia es una ecuación que define una secuencia recursiva;
cada término de la secuencia es definido como una función de términos anteriores

Ejemplo: máximo de comparaciones de la ordenación por intercalación

$$
\begin{equation}
  t(n) =
  \begin{cases}
    0 & \textup{si } n \in \{0, 1\} \\
    t(\lceil n/2 \rceil) + t(\lfloor n/2 \rfloor) + n - 1 & \text{si } n > 1
  \end{cases}
\end{equation}
$$

### DyV características

- hay una solución para los casos sencillos,
- para los complejos, se divide o descompone el problema en subproblemas:
  - cada subproblema es de igual naturaleza que el original,
  - el tamaño del subproblema es una fracción del original,
  - se resuelven los subproblemas apelando al mismo algoritmo,
- se combinan esas soluciones para obtener una solución del original.

### Forma general DyV

```cs
fun DyV(x) ret y
  if (x ∈ {simple}) then y := ad_hoc(x)
  else 
    problems: set{1..a} of typeof(x)
    solutions: set{1..a} of typeof(y)

    problems := descompose(x)

    for i := 1 to a do solutions{i} := DyV(problems{i}) od

    y := combine(solutions)
  fi
end fun 
```

normalmente los $x_i$ son fracciones de $x$
$|x_i| = \frac{|x|}{b}$
$b > 1$

- a = número de llamadas recursivas a DyV en una iteración
- b = relación entre el tamaño de $x$ y $x_i$ (satisface $|x_i| = \frac{|x|}{b}$)
- k = indica qué tan rápido crece el costo a medida que $n$ aumenta
  - el orden de descomponer y combinar es $O(n^k)$

### Conteo

Si queremos contar el costo computacional $t(n)$ de una función DyV:

$$
\begin{equation}
  t(n) =
  \begin{cases}
    c & \textup{si } \text{simple} \\
    a \times t(\frac{n}{b}) + g(n) & \textup{en caso contrario }
  \end{cases}
\end{equation}
$$

- $c$ es el costo de `ad_hoc()`
- $g(n)$ es el costo de `descompose()` y `combine()`

si $t(n)$ no es decreciente y $g(n)$ es del orden de $n^k$, entonces

$$
\begin{equation}
  t(n) \text{ es del orden de}
  \begin{cases}
    n^{\log_{b}{a}} & \textup{si } a > b^k \\
    n^k \log{n} & \textup{si } a = b^k \\
    n^k & \textup{si } a < b^k
  \end{cases}
\end{equation}
$$

### Ejemplos de DyV

- Merge Sort:
  - `x simple` = fragmento de arreglo de longitud 0 o 1
  - `descompose` = partir al medio (`b` = 2)
  - `a` = 2
  - `combine` = merge
- Quick Sort:
  - `x simple` = fragmento de arreglo de longitud 0 o 1
  - `descompose` = separar los menores de los mayores (`b` = 2)
  - `a` = 2
  - `combine` = yuxtaponer (`partition()`)

- Busqueda Binaria:

  ```cs
  {Pre: 1 ≤ lft ≤ n+1 ∧ 0 ≤ rgt ≤ n ∧ a ordenado}
  fun binary_search_rec (a: array[1..n] of T, x: T, lft, rgt: nat) ret i: nat
    var mid: nat

    //  si el subarray está vacío
    if lft > rgt → i := 0

    //  lft ≤ rgt
    else 
      //  se calcula el punto medio
      mid := (lft + rgt) ÷ 2
      if 
        //  si el elemento es menor, se busca en la mitad izquierda
        x < a[mid] → i := binary_search_rec(a, x, lft, mid - 1)
        
        //  si son el mismo, se selecciona
        x = a[mid] → i := mid

        //  si el elemento es mayor, se busca en la mitad derecha
        x > a[mid] → i := binary_search_rec(a, x, mid + 1, rgt)
      fi
    fi
  end fun
  {Post: (i = 0 ⇒ x no está en a[lft,rgt]) ∧ (i ̸= 0 ⇒ x = a[i])}
  ```

  ```cs
  {Pre: n ≥ 0 }
  fun binary_search (a: array[1..n] of T, x: T) ret i: nat
    //  se inicia la busqueda binaria
    i := binary_search_rec(a, x, 1, n)
  end fun
  {Post: (i = 0 ⇒ x no está en a) ∧ (i ̸= 0 ⇒ x = a[i])}
  ```

  - $t(n)$ = comparaciones que hace en el peor caso cuando el arreglo tiene $n$ celdas  
  - $a = 1,\ b = 2,\ k = 0$
  - $a = b^k$
  - $t(n)$ es del orden de $n^k \log{n}$, es decir del orden $\log{n}$

$$
  \begin{equation}
    t(n) =
    \begin{cases}
      0 & \textup{si } n = 0 \\
      t(\frac{n}{2}) + 1 & \textup{si } n > 0
    \end{cases}
  \end{equation}
$$  

## Tipos Concretos de Datos

- son provistos por el lenguaje de programación, decimos que son **nativos**
- **dependientes** del lenguaje
- enteros, char, string, booleanos, arreglos, reales, enums, tuplas, arrays, punteros

### Enums

- Serie finita de constantes

- definición:

```cs
type E = enum
          elem_1
          ...
          elem_k
        end enum
```

- declaración:

```cs
  var e: E
  e := elem_i
```

- ciclos for:

```cs
for i := elem_1 to elem_k do ... od
```

- sus elementos tendrán el orden en que fueron escritos en la definición.

```cs
elem_1 < elem_2 < ... < elem_k
```

### Tuplas

- También registros (records) o estructuras (structs)
- Las tuplas representan productos cartesianos de distintos tipos.
- Se puede definir un nuevo tipo mediante una tupla de la siguiente forma

```cs
type tperson = tuple
                name: string
                age: int  
                weight: float
              end tuple 
```

- El tipo tperson así definido corresponde al producto `string × nat × real`, y `name`, `age` y `weight` se llaman **campos**.

- declaración:

```cs
var manu: tperson
manu.name := "Emmanuel"
manu.age := 33
manu.weight := 68
```

### Arrays

- son colecciones de tamaño fijo de elementos del mismo tipo.
- el acceso a cada elemento es de tiempo constante
- declaración:

```cs
//  `a` tiene `N - M` elementos de tipo `T`
var a: array[M..N] of T
```

- tambien los hay multidimencionales

```cs
//  `b` tiene `(m - n) × (q - p)` elementos de tipo `string`
var b: array[n..m, p..q] of string

//  para acceder a un elemento:
b[i, j] := "bijota"
```

### Punteros

- Dado un tipo T, un **puntero a T**, es un tipo que representa la **dirección de memoria** de un elemento de tipo T.

```cs
var p: pointer to nat
```

Mediante punteros el programador puede manipular la memoria disponible al ejecutar un programa.

- Para reservar un bloque de memoria para almacenar un elemento se utiliza la operación `alloc`
- Puedo acceder al valor apuntado por `p` mediante la operación `*`

```cs
*p := 10
```

`p` apunta a 10

- Para liberar un bloque de memoria que reservado se utiliza `free`
- Existe una constante para representar punteros que no apuntan a nada, `null`

```cs
var p: pointer to tperson
alloc(p)

//  *p denota la tperson señalada por p

//  *p.field n permite acceder a la información alojada y modificarla
*p.name = "Juan"

//  Una notación conveniente para acceder a los campos de una tupla señalada por un puntero es la flecha "→"
p→name := "Juan"

//  son expresiones equivalentes
```

Los punteros permiten manejar explícitamente direcciones de memoria.  
Aparecen situaciones que con los tipos de datos usuales no se daban.

```cs
//  dos punteros apuntan a la misma direccion
q := p

//  ahora `*q` tambien es igual a `7`  
*p := 7

//  si quiero que `p` y `q` tengan el mismo valor pero que no se madifiquen entre ellas
*q := *p
```

## Tipos Abstractos de Datos (TADs)

- **surgen** de analizar el problema a resolver
- **independientes** del lenguaje
- se definen **especificando** constructores y operaciones
- se **implementan** usando concretos
- podemos tener varias implementaciones para un mismo TAD.
- El problema evidencia qué necesitamos representar y qué operaciones tener.

### Para especificar un TAD debemos

- Indicar su nombre
- Especificar constructores: procedimientos o funciones mediante los cuales puedo crear elementos del tipo que estoy especificando.
- Especificar operaciones: todos los procedimientos o funciones que permitirán manipular los elementos del tipo de datos que estoy especificando.
- Damos los prototipos de las funciones, y mediante lenguaje natural explicamos qué hacen.
- Algunas operaciones pueden tener restricciones que las indicamos mediante precondiciones.
- Debemos especificar también una operación de destrucción que libera la memoria utilizada por los elementos del tipo, en caso que sea necesario.

### Implementación de un TAD

- Definir un nuevo tipo con el nombre del TAD especificado. Para ello utilizamos tipos definidos previamente.
- Implementar cada constructor respetando los tipos tal como fueron especificados.
- Implementar cada operación respetando los tipos tal como fueron especificados.
- Implementar operación de destrucción liberando memoria si es que se ha reservado al construir los elementos.
- Pueden surgir nuevas restricciones que dependen de cómo implementamos el tipo.
- Puedo necesitar operaciones auxiliares que no están especificadas en el tipo.

### Listas

Las listas son colecciones de elementos de un mismo tipo, de tamaño variable.
Toda lista o bien es vacía o bien tiene al menos un elemento al comienzo.

Operaciones:

- decidir si una lista es vacía
- tomar el primer elemento
- tirar el primer elemento
- agregar un elemento al final
- obtener la cantidad de elementos
- concatenar dos listas
- obtener el elemento en una posición específica
- tomar una cantidad arbitraria de elementos
- tirar una cantidad arbitraria de elementos
- copiar una lista en una nueva

#### Especificacion Lista

```cs
spec List of T where
constructors

  fun empty() ret l: List of T
  {- crea una lista vacía. -}

  proc addl(in e: T, in/out l: List of T)
  {- agrega el elemento e al comienzo de la lista l. -}

destroy
  
  proc destroy(in/out l: List of T)
  {- Libera memoria en caso que sea necesario. -}

operations
  
  fun is_empty(l : List of T) ret b: bool
  {- Devuelve True si l es vacía. -}

  fun head(l: List of T) ret e: T
  {- Devuelve el primer elemento de la lista l -}
  {- PRE: not is_empty(l) -}

  ...
```

#### Implementación Lista

```cs
implement List of T where

type Node of T = tuple
                    elem: T
                    next: pointer to (Node of T)
                end tuple

type List of T = pointer to (Node of T)

fun empty() ret l: List of T
  l := null
end fun

proc addl(in e: T, in/out l: List of T)
  var p: pointer to (Node of T)
  alloc(p)
  p→elem := e
  p→next := l
  l := p
end proc

fun is_empty(l: List of T) ret b : bool
  b := l = null
end fun

{- PRE: not is_empty(l) -}
fun head(l: List of T) ret e: T
  e := l -> elem
end fun

...

proc destroy(in/out l: List of T)
  var aux: l
  do l != null->
    aux := l
    l := l -> next
    free(aux)
  od
end proc
```

### Pilas (Stacks)

La pila se define por lo que sabemos: sus cinco operaciones

- inicializar en vacía
- apilar una nueva obligación (o elemento)
- comprobar si está vacía
- examinar la primera obligación (si no está vacía)
- quitarla (si no está vacía).

las operaciones inicializar y agregar son capaces de generar todas las pilas posibles,  
comprobar y examinar solamente examinan la pila
quitarla no genera más valores que los obtenibles por inicializar y agregar  

#### Especificacion Pila

```cs
spec Stack of T where
constructors

  fun empty_stack() ret s: Stack of T
  {- crea una pila vacía. -}

  proc push(in e: T, in/out s: Stack of T)
  {- agrega el elemento `e` al tope de la pila s. -}

destroy
  
  proc destroy(in/out l: Stack of T)
  {- Libera memoria en caso que sea necesario. -}

operations
  
  fun is_empty_stack(s : Stack of T) ret b : Bool
  {- Devuelve True si la pila es vacía -}

  fun top(s : Stack of T) ret e : T
  {- Devuelve el elemento que se encuentra en el tope de s. -}
  {- PRE: not is_empty_stack(s) -}

  proc pop (in/out s : Stack of T)
  {- Elimina el elemento que se encuentra en el tope de s. -}
  {- PRE: not is_empty_stack(s) -}
```

### Colas (Queues)

Puede:

- inicializar vacía,
- agregar o encolar un dato,
- comprobar si quedan datos en el buffer, es decir, si es o no vacía
- examinar el primer dato (el más viejo de los que se encuentran en el buffer),
- quitar o decolar un dato.

El primer dato que se agregó, es el primero que debe enviarse y quitarse de la cola.
Las operaciones **vacía** y **encolar** son capaces de generar todas las colas posibles
**está vacía** y **primero**, en cambio, solamente examinan la cola,
**decolarla** no genera más valores que los obtenibles por vacía y apilar

#### Especificacion Cola

```cs
spec Queue of T where
constructors

  fun empty_queue() ret q: Queue of T
  {- crea una cola vacía. -}

  proc enqueue(in/out q: Queue of T, in e: T)
  {- agrega el elemento `e` al final de la cola `q`. -}

destroy
  
  proc destroy (in/out l: Stack of T)
  {- Libera memoria en caso que sea necesario. -}

operations
  
  fun is_empty_queue(q: Queue of T) ret b: Bool
  {- Devuelve True si la cola es vacía -}

  fun first(q: Queue of T) ret e: T
  {- Devuelve el elemento que se encuentra al comienzo de `q`. -}
  {- PRE: not is_empty_queue(q) -}

  proc dequeue(in/out q: Queue of T)
  {- Elimina el elemento que se encuentra al comienzo de `q`. -}
  {- PRE: not is_empty_queue(q) -}
```

## Algoritmos Voraces (Greedy)

Es la técnica más sencilla de resolución de problemas.  

Normalmente se trata de algoritmos que resuelven
problemas de optimización, es decir, tenemos un
problema que queremos resolver de manera óptima:

- el camino más corto que une dos ciudades,
- el valor máximo alcanzable entre ciertos objetos,
- el costo mínimo para proveer un cierto servicio,
- el menor número de billetes para pagar un cierto importe
- el menor tiempo necesario para realizar un trabajo, etc.

Los algoritmos voraces intentan construir la solución óptima buscada paso a paso,
eligiendo en cada paso la componente de la solución que parece más apropiada.

Caracteristicas:

- Nunca revisan una elección ya realizada
- Confían en haber elegido bien las componentes anteriores.
- No todos los problemas admiten solución voraz,
- Pero varios problemas interesantes sí admiten solución voraz,
- Dichas soluciones resultan muy eficientes

### Forma general

Ingredientes comunes de los algoritmos voraces

- se tiene un problema a resolver de manera óptima
- un conjunto de candidatos a integrar la solución,
- los candidatos se van clasificando en 3:
  - los aún no considerados,
  - los incorporados a la solución parcial,
  - los descartados,
- tenemos una manera de saber si los candidatos ya incorporados completan una solución del problema
- una función que comprueba si un candidato o un conjunto de candidatos es factible de formar parte de la solución
- otra función que selecciona de entre los candidatos aún no considerados, el más promisorio.

Receta de los algoritmos voraces

- inicialmente ningún candidato ha sido considerado,
- En cada paso se utiliza la función de selección para elegir cuál candidato considerar
- Se chequea que el candidato considerado sea factible para incorporarlo a la solución y se lo agrega o no
- Se repiten los pasos anteriores hasta que la colección de candidatos elegidos sea una solución

Esquema general:

```cs
//  p es un input con información del problema
fun voraz(C: Set of Candidate, p: ProbData) ret S: Solution
  var c: Candidate
  var p_aux: ProbData
  var C_aux: Set of Candidate
  
  S := base_solution()
  
  C_aux := set_copy(C)
  p_aux := p

  if(not problem_solvable(C, p)) -> S := error_solution()
  else
    do (not problem_is_solved(p_aux)) ->
      
      c := select_candidate(C)
      elim(C_aux, c)

      if is_feasible(c) ->
        S := modify_solution(S, c, p_aux)
        p_aux := modify_problem(p_aux, c)
      fi
    od
  fi
  set_destroy(C_aux)

end fun
```

## Voraces Sobre Grafos

### Arbol Generador de Costo Minimo

Sea G = (V, A) un grafo conexo no dirigido con un
costo no negativo asociado a cada arista.

Se dice que T ⊆ A es un árbol generador
si el grafo (V, T) es conexo y no contiene ciclos

Su costo es la suma de los costos de sus aristas.

Se busca T tal que su costo sea mínimo.

Hay 2 grandes ideas para encontrar el árbol generador de costo minimo:

- **Prim**: se parte desde un vértice origen y se va extendiendo a partir de ahí
  - en cada paso se une el tendido ya existente con alguno de los vértices aún no alcanzados, seleccionando la arista de menor costo capaz de incorporar un nuevo vértice

- **Kruskal**

#### Prim: Implementación

Podemos representar los grafos como una tupla con dos conjuntos:
uno para los vértices y otro para las aristas

```cs
type Vertex = Nat;

type Edge = tuple
              v1: Vertex
              v2: Vertex
              cost: Nat
            end tuple;

type Graph = tuple
              vertices: Set of Vertex
              edges: Set of Edge
            end tuple;  

fun Prim(G: Graph, i: Vertex) ret T: Set of Edge
  //  las aristas de G son los candidatos

  //  c: Candidate
  var e: Edge
  var V: Set of Vertex
  
  //  se crea una copia del set para administrar vértices no visitados
  V := copy_set(G.vertices)

  //  se elimina el vértice inicial, ya fué visitado
  elim(V, i)

  //  se inicializa la solución
  T := empty_set()
  
  //  se añade el vértice inicial a la solución
  add(T, i)

  //  hasta que todos los vértices hayan sido visitados
  do (not is_empty_set(V)) ->
    
    /**  
     * selecciono una arista tal que uno solo de sus extremos esté en el set
     * un vértice es visitado y el otro no
     * 
     * quedando este conjunto como posibles candidatos
     * {(e.v1 ∈ V ∧ e.v2 ∉ V) ∨ (e.v1 ∉ V ∧ e.v2 ∈ V)}
     *  
     * elijo de ese conjunto la arista con menor costo
     */
    e := "selecciono arista de costo minimo tal que (e.v1 ∈ V ∧ e.v2 ∉ V) ∨ (e.v1 ∉ V ∧ e.v2 ∈ V)"
    
    //  elimino el vértice visitado por e
    if member(e.v1, V) ->
      elim(V, e.v1)
    else
      elim(V, e.v2)
    fi

    //  agrego e a la respuesta
    add(T, e)
  od
end fun
```

### Camino de Costo Minimo

Sea G = (V, A) un grafo dirigido con costos no negativos
en sus aristas, y sea v ∈ V uno de sus vértices.

Se busca obtener los caminos de menor costo desde v
hacia cada uno de los demás vértices.

#### Dijkstra

El algoritmo de Dijkstra realiza una secuencia de n pasos,
donde n es el número de vértices

En cada paso, “aprende” el camino de menor costo desde
v a un nuevo vértice.

Marca a ese nuevo vértice

Tras esos n pasos, conoce los costos de los caminos de
menor costo a cada uno de los vértices del grafo.

##### El Algoritmo

- Asumiremos que el grafo viene dado por un conjunto de vértices
  - `V = {1, ..., n}`

- y los costos por una matriz
  - `L: array[1..n, 1..n] of Nat`
  - `L[i, j]` mantiene el costo de la arista que va de `i` a `j`
  - En caso de no haber ninguna arista de `i` a `j`, `L[i, j] = ∞`.
  - `L[i, i] = 0`

- Esta versión del algoritmo , halla sólo el **costo** del camino, en vez de hallar el camino de costo mínimo  
  - Hallará el **costo del camino de costo mínimo** desde un vértice `v`

- El resultado estará dado por un arreglo
  - `D: array[1..n] of Nat` (se asume costo natural)
  - en `D[j]` se guarda el costo de `v` a `j`

```cs
fun Dijkstra(L: array[1..n, 1..n] of Vertex, v: Vertex) ret D: array[1..n] of Nat
  
  //  C es el conjunto de los vértices que todavía desconocemos cuál es el camino de menor costo
  var C: Set of Vertex
  var c: Vertex
  
  //  Se inicializa el set C con todos los vértices
  for i := 1 to n do add(C, i) od

  //  Se elimina el vértice inicial de C
  elim(C, v)

  //  Se inicializa la solución con los valores iniciales de los costos desde v
  for j := 1 to n do D[j] := L[v, j] od

  //  hasta que todos los vértices hayan sido visitados
  do (not is_empty_set(C))→
    
    //  visito el vértice de menor costo que todavía no haya sido visitado
    c := “elijo elemento c de C tal que D[c] sea mínimo”

    //  elimino el vértice visitado por c
    elim(C, c)

    //  actualizo los costos teniendo en cuenta el nuevo vértice visitado
    for j in C do 
      /**  
       * me quedo con el mínimo entre el costo actual, o 
       * la suma entre el costo al nuevo vértice y el costo del nuevo vértice a los otros
       */
      D[j] := min(D[j], D[c] + L[c, j]) 
    od
  od
end fun
```

## Backtracking

### Forma General Backtracking

```cs
//  i es un entero que representa el candidato actual
fun backtracking(C: array[1..n] of Candidate, i: Nat, p : ProbData) ret S : Solution
  
  //  si el problema es simple -> se resuelve
  if(problem_easy(p)) -> S := base_solution(p)
  
  //  si se llega al final del arreglo y todavia no se solucionó -> solucion para error
  else if(i = 0) -> S := error_solution(p)

  //  si no es factible usar el candidato actual, se saltea
  else if(not is_feasible(C[i])) -> S := backtracking(C, i - 1, p)
  
  // en caso contrario
  else -> S := 
    //  se comparan las soluciones
    pick_solution(
      //  salteando el candidato actual
      backtracking(C, i - 1, p), 
      //  usando el candidato actual
      use_candidate(
        backtracking(C, i, modify_problem(p, C[i]))
      )
    ) 
  fi

end fun
```

### Forma Matemática Backtracking

`backtracking` -> $bT()$
`pick_solution()` -> $pS()$  
`use_candidate()` -> $uC()$
`modify_problem()` -> $mP()$  

$$
\begin{equation}
  bT(i, p) =
  \begin{cases}
    base\text{-}solution(p) & \textup{si } problem\text{-}easy(p) \\
    error\text{-}solution(p) & \textup{si } i = 0 \land \neg problem\text{-}easy(p)\\
    bT(i - 1, p) & \textup{si } \neg is\text{-}feasible(d_i) \\
    pS(bT(i - 1, p), uC(bT(i, mP(p, d_i)))) & \textup{en caso contrario}
  \end{cases}
\end{equation}
$$

no siempre son necesarios el caso erroneo o el caso de salteo  
