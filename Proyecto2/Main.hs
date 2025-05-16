import ModeloUsuarios
import Cifrado
import System.IO (hFlush, stdout)

main :: IO ()
main = menuPrincipal

-- Menú principal con repetición
menuPrincipal :: IO ()
menuPrincipal = do
    putStrLn "\n===== MENU PRINCIPAL ====="
    putStrLn "1. Crear usuario y validar PIN"
    putStrLn "2. Probar cifrado de un mensaje"
    putStrLn "3. Salir"
    putStr "Seleccione una opcion: "
    hFlush stdout
    opcion <- getLine
    case opcion of
        "1" -> opcionValidarUsuario >> menuPrincipal
        "2" -> opcionProbarCifrado >> menuPrincipal
        "3" -> putStrLn "Saliendo del programa. ¡Hasta luego!"
        _   -> putStrLn "Opcion invalida, intente de nuevo." >> menuPrincipal

-- Opción 1: Crear usuario y validar PIN
opcionValidarUsuario :: IO ()
opcionValidarUsuario = do
    putStrLn "\n=== CREAR USUARIO Y VALIDAR PIN ==="
    putStr "Ingrese el nombre del usuario: "
    hFlush stdout
    nombre <- getLine
    putStr "Ingrese el PIN del usuario: "
    hFlush stdout
    pinCreado <- getLine

    let usuario = crearUsuario nombre pinCreado
    putStrLn ("Usuario creado: " ++ show usuario)

    putStr "Ingrese el PIN para validar: "
    hFlush stdout
    pinIngresado <- getLine

    if validarPin usuario pinIngresado
        then putStrLn "PIN correcto."
        else putStrLn "PIN incorrecto."

-- Opción 2: Probar el cifrado simple
opcionProbarCifrado :: IO ()
opcionProbarCifrado = do
    putStrLn "\n=== PRUEBA DE CIFRADO ==="
    putStr "Ingrese la clave (PIN): "
    hFlush stdout
    clave <- getLine
    putStr "Ingrese el mensaje a cifrar: "
    hFlush stdout
    mensaje <- getLine

    let cifrado = cifrarConXor clave mensaje
    let descifrado = cifrarConXor clave cifrado

    putStrLn ("Mensaje cifrado: " ++ cifrado)
    putStrLn ("Mensaje descifrado: " ++ descifrado)
