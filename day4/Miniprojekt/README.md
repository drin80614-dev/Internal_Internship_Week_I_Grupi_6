# Console-based Student Progress Tracker in C

Ky mini-projekt eshte nje aplikacion i thjeshte ne console per menaxhimin e disa regjistrimeve te progresit te nxenesve brenda te njejtit ekzekutim. Struktura eshte mbajtur e paster dhe e ndare ne funksione qe projekti te zgjerohet me vone pa rishkruar logjiken baze.

## Struktura e projektit

```text
Miniprojekt/
|-- include/
|   `-- student_tracker.h
|-- src/
|   |-- main.c
|   `-- student_tracker.c
`-- README.md
```

## Si funksionon

- Programi hapet me nje menu ne console dhe mundeson shtimin e disa regjistrimeve radhazi.
- Zgjedhjet kryesore trajtohen me `switch`.
- Regjistrimet ruhen ne nje array fiks me kapacitet `MAX_STUDENTS`, ndersa `recordCount` mban numrin aktual te regjistrimeve.
- `enum` perdoret per statusin e progresit.
- Programi ka edhe nje raport analitik me permbledhje te shkurter mbi te dhenat e ruajtura.
- Programi ka edhe kerkim, perditesim me pointer dhe renditje sipas progresit.
- Nje pointer perdoret praktikisht ne funksionin `addStudentRecord` per te punuar me regjistrimin aktual dhe per te perditesuar `recordCount`.
- `if/else` perdoret per validimin e input-it dhe per vendime logjike.
- Loop `while` mban aktive menune dhe `for` shfaq listen e regjistrimeve ne format te rregullt.
- Loop `for` perdoret edhe per llogaritjet e raportit analitik.
- Nje kopje e sigurt e array-it perdoret per renditjen sipas progresit pa prishur rendin origjinal.
- Kur arrihet kufiri maksimal, programi shfaq mesazh te qarte dhe vazhdon te funksionoje normalisht.

## Kompilimi

Me `gcc`:

```bash
gcc src/main.c src/student_tracker.c -o student_tracker
```

Ekzekutimi:

```bash
./student_tracker
```

Ne Windows me MinGW:

```bash
gcc src/main.c src/student_tracker.c -o student_tracker.exe
student_tracker.exe
```

## Shembull i shkurter i perdorimit

```text
===== Student Progress Tracker =====
Regjistrime aktive: 0 / 10
1. Shto regjistrim te ri
2. Shfaq te gjithe regjistrimet
3. Shfaq raportin analitik
4. Kerko regjistrime
5. Perditeso nje regjistrim ekzistues
6. Shfaq renditjen sipas progresit
7. Dil nga programi
Zgjidh nje opsion: 1

Vendos ID: 101
Vendos emrin e nxenesit: Arta Hoxha
Vendos progresin/rezultatin: 88.5
Zgjidh statusin:
1. Below Target
2. On Track
3. Completed
Statusi: 2
Regjistrimi u shtua me sukses.

===== Student Progress Tracker =====
Regjistrime aktive: 1 / 10
1. Shto regjistrim te ri
2. Shfaq te gjithe regjistrimet
3. Shfaq raportin analitik
4. Kerko regjistrime
5. Perditeso nje regjistrim ekzistues
6. Shfaq renditjen sipas progresit
7. Dil nga programi
Zgjidh nje opsion: 3

=========================== Raporti Analitik ===========================
Totali i regjistrimeve : 2
Mesatarja e progresit  : 91.25
Progresi me i larte    : 94.00
Progresi me i ulet     : 88.50
Regjistrime Completed  : 1
-----------------------------------------------------------------------
Interpretim: Ka pak te dhena, ndaj raporti eshte ende fillestar.
Mesatarja: Progresi i pergjithshem eshte i larte.
Completed: Numri i regjistrimeve te perfunduara eshte i kenaqshem.

Zgjidh nje opsion: 2

============================== Lista e Regjistrimeve ==============================
ID     Emri                      Progresi     Statusi
-----------------------------------------------------------------------------------
101    Arta Hoxha                88.50        On Track
102    Leon Daka                 94.00        Completed
-----------------------------------------------------------------------------------
Totali i regjistrimeve: 2

Zgjidh nje opsion: 6

=========================== Renditja Sipas Progresit ===========================
Rank   ID     Emri                      Progresi     Statusi
-----------------------------------------------------------------------------------
1      102    Leon Daka                 94.00        Completed
2      101    Arta Hoxha                88.50        On Track
-----------------------------------------------------------------------------------
Renditja u krijua nga vlerat reale te progresit pa ndryshuar rendin origjinal.
```

## Pjese qe mund te zgjerohen me vone

- Shtimi i opsioneve per editim te regjistrimeve ekzistuese
- Fshirja e nje regjistrimi sipas ID-se
- Kerkimi i nje nxenesi sipas emrit ose ID-se
- Llogaritja e statistikave si mesatarja e progresit
- Ruajtja e te dhenave ne file per perdorim pas mbylljes se programit
- Renditja e regjistrimeve sipas emrit, rezultatit ose statusit
- Filtrimi i regjistrimeve sipas statusit te progresit
- Raporte me te avancuara sipas intervaleve te rezultateve ose statusit
- Eksportimi i renditjes ose raporteve ne file
- Ndarja e logjikes ne module shtese si `validation`, `reports` ose `storage`

## Vazhdueshmeria e projektit

Ky version i zgjeruar menaxhon disa regjistrime ne menyre me te qarte dhe me te qendrueshme, por projekti eshte ende i hapur per funksione te reja. Do te kete kod shtese, permiresime dhe zgjerime te tjera me vone, sidomos per menaxhim me te plote te regjistrimeve, validim me te mire dhe raportim me te avancuar.

## Hapat Finale me Git/GitHub

- Bej commit me mesazhe te qarta dhe kuptimplota, p.sh. `Add progress ranking feature` ose `Finalize student tracker cleanup`
- Pusho ndryshimet ne branch-in tend personal, jo ne `main`
- Para dorezimit, verifiko qe te gjitha kerkesat e dites jane te perfshira dhe funksionojne ne projekt
