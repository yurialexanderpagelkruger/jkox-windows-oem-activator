# JKOX

**JKOX** es una herramienta de extracción y activación de licencias de Windows escrita en C++ nativo. Diseñada específicamente para técnicos, administradores de sistemas y usuarios que buscan una solución rápida y sin fricción, *JKOX* reemplaza los comandos manuales de consola por una experiencia de terminal limpia, estética y portable.

Con un flujo directo y asistido, la aplicación permite inspeccionar la placa madre en busca de claves embebidas de fábrica (OEM), aplicarlas automáticamente o activar licencias retail/volumen de forma guiada, todo desde un único binario independiente.

## 📸 Capturas de pantalla

*Menú principal en terminal con arte ASCII temático, velas pixel-art y paleta en cian y amarillo fuego.*

## ✨ Características Principales

* **Diseño Terminal Retro & Pixel Art:** Cabecera estilizada en ASCII con velas simétricas detalladas (`(*)`) y paleta de colores Win32 optimizada (cian brillante, blanco puro, gris técnico y acentos dorados).

* **Lectura Nativa de Firmware:** Acceso directo a la tabla ACPI `MSDM` del BIOS/UEFI mediante llamadas nativas de bajo nivel (`GetSystemFirmwareTable`), sin intermediarios lentos ni dependencias de PowerShell.

* **Portabilidad Absoluta:** Compilado de forma estática (`/MT`). Un único archivo `.exe` ligero (\~240 KB), sin instaladores, sin runtime de Visual C++ requerido y listo para usar desde un pendrive en cualquier PC con Windows.

* **Sanitizador Inteligente de Claves:** Formateador automático para claves manuales que remueve espacios, normaliza mayúsculas y añade los guiones cada 5 caracteres de forma transparente.

* **Elevación UAC Embebida:** Manifiesto de ejecución integrado que solicita permisos de Administrador de forma nativa desde el inicio.

* **Internacional y Limpio:** Salida estándar en inglés técnico y ejecución desatendida mediante el host `cscript //nologo` para evitar ventanas emergentes molestas de Windows Script Host.

## ⚙️ ¿Qué hace la aplicación? (Opciones disponibles)

Desde el menú de consola, *JKOX* permite ejecutar las siguientes operaciones:

1. **Auto OEM Activation:** Extrae la clave de producto original incrustada de fábrica en la tabla ACPI/MSDM del motherboard, la instala en el sistema (`slmgr /ipk`), conecta con los servidores de validación de Microsoft (`slmgr /ato`) y valida el resultado final.

2. **Display Embedded OEM Key Only:** Inspecciona y muestra en pantalla la clave OEM de la placa madre sin realizar ninguna modificación ni alterar el estado de la licencia actual.

3. **Manual Key Input & Activation:** Permite ingresar manualmente una clave de producto (Retail, OEM o Volumen), sanitiza el texto a 25 caracteres alfanuméricos y la activa contra los servidores de activación.

4. **Check Current Activation Status:** Consulta el estado actual de licenciamiento y expiración del sistema operativo mediante `slmgr /dli` y `slmgr /xpr`.

5. **Exit:** Cierre seguro del programa.

## 🛠️ Tecnologías Utilizadas

* **Lenguaje:** C++17

* **APIs del Sistema:** Windows API (`GetSystemFirmwareTable`, Win32 Console API, Desktop Shell).

* **Subsistema:** Windows Licensing Tool (`slmgr.vbs` interactuando vía `cscript`).

* **Enlace de Binario:** Static Runtime (`/MT`) x64.

* **Entorno de Desarrollo:** Visual Studio Enterprise 2026.

## 🚀 Instalación y Uso

1. Descarga el ejecutable `jkox.exe` desde la sección de [**Releases**](../../releases).

2. Haz doble clic en `jkox.exe` para iniciarlo.

3. *Nota:* La aplicación solicitará automáticamente permisos de **Administrador (UAC)**, ya que el servicio de licencias de Windows (`slmgr`) requiere privilegios elevados para registrar claves.

4. Selecciona la opción deseada (ej. `[1]` para activación automática OEM) y deja que la herramienta complete el proceso.

## 👨‍💻 Autor

Creado por **Yuri Alexander Pagel Krüger**