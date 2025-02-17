# Encriptador de Archivos - Parcial Sistemas Operativos

Que mas profe! Este es nuestro proyecto para el parcial de SO. Implementamos un programa para encriptar archivos usando las llamadas al sistema que vimos en clase. Esta super bueno porque detecta si el archivo es binario o texto y lo encripta usando XOR.

## Que hace el programa?

- Detecta automáticamente si el archivo es de texto o binario
- Encripta y desencripta archivos con XOR (nada de librerias externas como dijo en clase)
- Todo por terminal, bien old school
- Solo usa llamadas al sistema de Linux (open, read, write, close)
- Cero dependencias externas porque no nos gusto ninguna jaja

## Como funciona la encriptación?

La verdad es bastante simple (pero funciona):
- Agarra cada byte y le hace XOR con una llave fija (0xAE)
- La misma operación sirve para encriptar y desencriptar (eso fue intencional, lo juro)
- Funciona con cualquier tipo de archivo

## Que necesitas para que funcione?

- Linux (obvio)
- G++ que soporte C++17
- Make 

## Como se compila esta vaina?

Super facil, en la terminal:

```bash
make
```

Y listo, ya tienes el ejecutable `fileencrypt`.

Si quieres borrar todo lo compilado:
```bash
make clean
```

## Como se usa?

Tenemos varios comandos (igual que los que pidio en el enunciado):

1. Si no sabes que hacer, la ayuda:
```bash
./fileencrypt -h
```

2. Ver la version (por si acaso):
```bash
./fileencrypt -v
```

3. Encriptar un archivo:
```bash
./fileencrypt -e archivo.txt
```

4. Desencriptar (para cuando necesites ver que escribiste):
```bash
./fileencrypt -d archivo.txt.encrypted
```

## Pruebalo tu mismo

### Primer intento: Encriptar algo

```bash
echo "Parcial de SO" > test.txt
./fileencrypt -e test.txt
```

Deberia salir algo asi:
```
Tipo de archivo: texto
Archivo encriptado guardado como: test.txt.encrypted
```

### Ahora desencriptalo

```bash
./fileencrypt -d test.txt.encrypted
```

Y te debe salir:
```
Archivo desencriptado guardado como: test.txt.encrypted.decrypted
```

Para ver si funciono:
```bash
cat test.txt.encrypted.decrypted
# Deberia mostrar: Parcial de SO
```

## Que archivos hicimos?

- `main.cpp`: El main normal de siempre
- `FileEncryption.h`: La clase que hace la magia
- `FileEncryption.cpp`: Donde esta todo el codigo importante
- `Makefile`: Para compilar facil

## Como funciona por dentro?

Usamos las llamadas al sistema que vimos en clase:
- `open()`: Pa' abrir archivos
- `read()`: Pa' leer
- `write()`: Pa' escribir
- `close()`: Pa' cerrar (importante no olvidarse de esto)

La parte chida es que detecta si el archivo es binario o texto revisando los primeros 1024 bytes.

## Que le falta?

- La clave de encriptacion es fija (podriamos dejar que el usuario la ponga)
- No comprime nada
- No lleva un registro de que archivos estan encriptados
- A veces tira errores si el archivo es muy raro

## Que se podria mejorar?

Si tuvieramos mas tiempo (y no fuera pal miercoles) podriamos:
- Dejar que el usuario ponga su propia clave
- Meterle compresion aqui mismo pero esta en otro archivo
- Verificar que no se dañe nada
- Hacer que funcione con carpetas completas

## Nota de seguridad (importante)

Profe, sabemos que este no es el algoritmo mas seguro del mundo. Es mas pa' demostrar que entendimos las llamadas al sistema. No lo uses para guardar las respuestas del siguiente parcial xd.