application {
	class model.MainClass representation model.MainClass.stm32f334r8
	class SystemLib.Miscellaneous.DeltaTimeService
}
schedule {
	startup {
	}
	shutdown {
	}
	task Task_5ms priority 0 period 5ms delay 0ms {
		process model.MainClass.step
	}
}