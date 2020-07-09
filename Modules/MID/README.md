### Producing digits in raw format with a MC simulaiton

```bash
o2-sim -g fwmugen -m MID -n 100
o2-sim-digitizer-workflow 
o2-mid-digits-to-raw-workflow 
```

### Task + check example on raw MC digits

```bash
o2-raw-file-reader-workflow --input-conf MIDraw.cfg --message-per-tf | o2-qc-run-mid
```

