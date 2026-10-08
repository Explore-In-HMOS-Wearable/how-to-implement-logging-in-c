import testNapi from 'libentry.so';
import { hilog } from '@kit.PerformanceAnalysisKit';

@Entry
@Component
struct Index {
  @State message: string = 'Ready';

  build() {
    Column({ space: 10 }) {
      Text(this.message).fontSize(16)

      Button('Add')
        .onClick(() => {
          const sonuc = testNapi.add(60, 50);
          hilog.info(0x3200, 'MyArkTS', 'Sum: %{public}d', sonuc);
          this.message = `Sum: ${sonuc}`;
        })

      Button('Divide (10/0)')
        .onClick(() => {
          const sonuc = testNapi.divide(10, 0);
          hilog.info(0x3200, 'MyArkTS', 'Quotient: %{public}d', sonuc);
          this.message = `Quotient: ${sonuc}`;
        })

      Button('Log Demo')
        .onClick(() => {
          testNapi.logDemo();
          this.message = 'Logs printed';
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}