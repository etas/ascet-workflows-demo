# EUnitSupport Library

The target ESDL test project must explicitly reference the `EUnitSupport` project to gain access to its packages.

## The `assert` Package

This package provides assertion methods to write ESDL unit tests.

Note that no concrete assertion logic is included. All provided functions are in form of interfaces (external ESDL methods).
During test execution, the actual assertions are expanded to an underlying testing framework (GoogleTest by default) accordingly.

Every test class must have an instance of the `Assert` class as one of its fields.

```esdl
import assert.Assert;

singleton class Test {
    Assert assert;

    @Test
    public void test() {
        assert.assertEqual(2.0, 1.0 + 1.0);
    }
}
```

## The `time` Package

In an application context (PC Experiment, ECU, ...), the underlying operating system or the simulation environment is taking care
of setting the `@dT` variable. It is updated before each task is run so that you can rely on it in your computations (think of a
class integrating values over time for example). This is why it is generally not allowed to write the `@dT` variable in your
models.

In unit tests, however, there is no application context and no underlying environment taking care of setting the current time
difference. In order to be able to test your computations depending on `@dT`, the `DeltaTimeAccess` class allows us to set the
value manually in EUnit tests. Since every test method runs independent of tasks and scheduling rules, it is safe to access and
especially write `@dT` directly.

Every test class must have an instance of the `DeltaTimeAccess` class as one of its fields.

```esdl
import assert.Assert;
import time.DeltaTimeAccess;

singleton class Test {
    Assert assert;
    DeltaTimeAccess time;

    @Test
    public void test() {
        time.setDeltaTime(7.0);
        assert.assertEqual(time.getDeltaTime(), 7.0);

        time.setDeltaTime(12.0);
        assert.assertEqual(time.getDeltaTime(), 12.0);
    }
}
```
