ahora mismo funciona bien , sin leaks ni segfault etc 
contemplado iniciar sin environ
contemplado elimincacion de variables de entorno durante la ejecución
contemplado errores de sintaxis
contemplado elimnación de pwd meddiante eliminacion de directorios
contemplado heredoc mediante redirección
contemplado comillas simples y dobles (tokenización)
contemplado expansiones
contemplado limpieza comillas una vez tokenizado y expandido 
contempladas las señales y g_signal para el status de exito o no de ejecución
realizados builtins y executables
realizado pipex y redirecciones
flujo:
lectura en readline
comprobaciones: nulo , enter, control c etc
tokenización meidante comillas o espacios
comprobación de pipex
comprobación de redirecciones
comprobación de builtnins
comprobación de ejecutables.
En cada caso anterios si es alguna de esas comprobaciones tomara ese camino y se crear la estructura cmd en base a esa comprobacion , 
la estructura cmd se crea en parse redirect ya que lo cree antes de pipexx, entpnces se usa para ambos casos para crear la estructura cmd, en caso 
de ser varios pipex se enlazara a esa estructura el siguuente nodo con la misma estructura , y asi creas una lista de nodos 

Las dos unicas cosas que no funciona como deberia, no causa leaks ni segfault ni cierra el programa:
1 cuando se ejecuta en minishell export rbs=ls -a lo hace bien y solo coge ls como arg, pero si es export rbs="ls -a" deberia de coger las dos por separado 
y ejecutar ls -a pero muestra command not found "ls -a" por que no lo separa.
Este caso es rebuscado no sale en el subject y a mucha gente no se lo ejecuan ,por eso no se que hacer si arreglaro o no.
2 el siguiente es solo cundo estas dentrode varios heredocs control c devuelve bien el prompt cuando es el ultimo heredoc , 
si se ejecuta contrl c durante los heredoc anteriores al ultimo sigeu esperando los heredocs
Al iguel que antes casi rebuscao etc este caso creo que seria mas complejo de resolver que el anterior
por eso mi duda es, tiramoos palante y presentamos ya que con la mayoria de gente que he hablado y la han probado a tope la ven bien 
o por  el contrario intenteamos arreglar esto , yo creo qu elo de rbs="ls -a" lo puedo hacer en un par de  dias como mucho 
