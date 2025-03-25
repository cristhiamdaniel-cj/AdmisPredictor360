import struct

def read_student_binary(filename):
    """
    Lee el archivo binario que contiene un arreglo de estructuras Student y 
    devuelve una lista de diccionarios con los datos.
    
    Cada registro se escribe en C++ con el siguiente formato:
      int serialNo, int GRE Score, int TOEFL Score, int University Rating,
      double SOP, double LOR, double CGPA, int Research, double Chance of Admit.
    
    Se asume que el archivo comienza con un entero sin signo (8 bytes, formato "Q")
    que indica el número de registros.
    """
    students = []
    with open(filename, "rb") as f:
        count_bytes = f.read(8)
        if len(count_bytes) < 8:
            raise ValueError("No se pudo leer el número de registros.")
        count = struct.unpack("Q", count_bytes)[0]
        fmt = "iiiidddid"  # 4 ints, 3 doubles, 1 int, 1 double.
        size = struct.calcsize(fmt)
        for _ in range(count):
            data = f.read(size)
            if len(data) != size:
                break
            values = struct.unpack(fmt, data)
            student = {
                "Serial No.": values[0],
                "GRE Score": values[1],
                "TOEFL Score": values[2],
                "University Rating": values[3],
                "SOP": values[4],
                "LOR": values[5],
                "CGPA": values[6],
                "Research": values[7],
                "Chance of Admit": values[8],
            }
            students.append(student)
    return students
