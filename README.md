# scurve
cubic spline interpolation, original version by simpsonyin 20140829

# last modified
refactoring. Sep. 2023

# pseudo-codes

```
vector<scurve::Spoint> pts;
...
scurve::Sspline curve(pts.size(), pts.data());
...
for (int section = 1; section < fpoints.size(); ++section) {
  ...
  auto len = curve.chordLength(section);
  // t[0, 1.0]
  auto p = curve.curvept(t * len, section);
  ...
}
```
