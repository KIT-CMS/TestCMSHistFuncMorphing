# TestCMSHistFuncMorphing

## Setting up morphed datacard

```bash
testMorph; mv test_morph.root CombineHarvester/TestCMSHistFuncMorphing/shapes/
```

## Creating workspace

```bash
combineTool.py -M T2W -o "ws.root" -i output_testMorph/
```

## Creating morphed prefit shapes

```bash
for m in 5 10 12.5 15 20 25
do
  PostFitShapesFromWorkspace -m ${m} -w output_testMorph/ws.root -o output_testMorph/prefit_shapes_${m}.root > ${m}.log
done
```

## Plot morphed shapes
```bash
morphed_shapes.py
```
