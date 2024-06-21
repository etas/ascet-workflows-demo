application {
	class simulation.Stimulator
	class model.MainClass
	class SystemLib.Miscellaneous.DeltaTimeService
}
schedule {
	startup {
	}
	shutdown {
	}
	task Task0 priority 0 period 10ms delay 0ms {
		process simulation.Stimulator.stimulate
		process model.MainClass.step
	}
}