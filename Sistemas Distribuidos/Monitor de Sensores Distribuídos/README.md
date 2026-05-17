## Compilacao

```powershell
javac -d out src/monitor/*.java
```

## Execucao

1. Inicie o servidor:

```powershell
java -cp out monitor.SensorHubServer
```

2. Em outro terminal, inicie o cliente:

```powershell
java -cp out monitor.MonitorClient
```