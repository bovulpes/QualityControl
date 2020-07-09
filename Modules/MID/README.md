### Producing digits in raw format with a MC simulation

```bash
o2-sim -g fwmugen -m MID -n 100
o2-sim-digitizer-workflow 
o2-mid-digits-to-raw-workflow 
```

### Task + check example on raw MC digits

```bash
o2-raw-file-reader-workflow --input-conf MIDraw.cfg --message-per-tf | o2-qc-run-mid
```

### Note

Using O2 branch with modifications (creation of MFTWorkflow library in Detectors/MUON/MID/Workflow/CMakeLists.txt):

```bash
https://github.com/bovulpes/AliceO2/tree/mid
```
