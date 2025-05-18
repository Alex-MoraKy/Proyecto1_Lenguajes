-- Manejo de archivos

module ManejoArchivos (agregarAlFinal, leerLinea, abrirArchivo, cerrarArchivo, listarTxt, crearArchivo) where
import System.IO
import System.Directory (getDirectoryContents) --funcion para ver el contenido de un directorio
import Data.List (isSuffixOf) --Funcion para ver la terminacion de un string

-- Esto escribe por la linea por la que va el archivo
agregarAlFinal :: FilePath -> String -> IO ()
agregarAlFinal archivo string = do
    handle <- openFile archivo AppendMode
    hPutStrLn handle string
    hClose handle


crearArchivo :: FilePath -> IO ()
crearArchivo rutaContenido = do
  handle <- openFile rutaContenido WriteMode
  hClose handle


abrirArchivo :: FilePath -> IO Handle
abrirArchivo ruta = openFile ruta ReadMode

cerrarArchivo :: Handle -> IO ()
cerrarArchivo handle = hClose handle

leerLinea :: Handle -> IO String
leerLinea handle = hGetLine handle


-- Esta funcion lista todos los txts de un directorio 
-- la usamos para ver todos los archivos de usuarios que hayan
listarTxt :: FilePath -> IO [FilePath]
listarTxt carpeta = do
  archivos <- getDirectoryContents carpeta
  let txtFiles = filter (".txt" `isSuffixOf`) archivos
  return txtFiles


leerLineas :: Handle -> IO ()
leerLineas handle = do
    fin <- hIsEOF handle
    if fin
        then return ()
        else do
            linea <- hGetLine handle
            putStrLn ("Línea: " ++ linea)
            leerLineas handle

copiarArchivo :: IO ()
copiarArchivo = do
    inHandle  <- openFile "entrada.txt" ReadMode
    outHandle <- openFile "copia.txt" WriteMode
    copiarLineas inHandle outHandle
    hClose inHandle
    hClose outHandle

copiarLineas :: Handle -> Handle -> IO ()
copiarLineas hin hout = do
    eof <- hIsEOF hin
    if eof
        then return ()
        else do
            linea <- hGetLine hin
            hPutStrLn hout linea
            copiarLineas hin hout