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

### Algoritmo

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

### Algoritmo

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
$ b > 1$

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
