:: DSA_assignments\A01_WordCountFromFileUsingOwnVector

dir

del vector_file_wordCount_client.exe vector_file_wordCount_client.obj vector_file_wordCount_server.obj

dir

cl.exe vector_file_wordCount_client.c vector_file_wordCount_server.c /c /EHsc

dir

link.exe vector_file_wordCount_client.obj vector_file_wordCount_server.obj

dir

vector_file_wordCount_client.exe test_file.txt Sugriv

