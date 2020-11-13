OpenFOAMのオブジェクト関連の仕組みを整理する。  
例題としてここで「inletとoutletのphiの総和をscoreとして出力する」をいろいろな方法で行う。

## 001.codedFunctionObject

### orgCase

- 例としてTJunction/pimpleFoamを用意。
- スコアの計算と出力を既存機能で表現。

## codedCase

- スコアの計算と出力をcodedFunctionObjectで行う。
- ついでにawkなどを使ってlogファイルから時間とscoreを抽出する

## 002.inSolver

### scorePimpleFoam

- スコアの計算と出力をソルバーの中で行う。

### planeCase

- functionObjectなど無しでただ上記ソルバーを実行するだけのケース。

## 003.class

### scoreClassPimpleFoam

- スコアの計算と出力を行うclass "getScore"を作成する
- これをソルバーの中でincludeして使用する。

## 004.inheritance

### scoreInheritancePimpleFoam

- 以下のように分担する。
  - スコアの計算：sumInletOutletScore
  - スコアの出力：getScore
- sumInletOutletScoreは"getScore"を継承しているためスコアの出力ができる
- ソルバーの中ではsumInletOutletScoreをincludeする。
