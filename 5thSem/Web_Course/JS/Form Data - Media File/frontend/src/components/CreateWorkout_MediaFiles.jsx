import { useState } from "react";
import api from "../api/axios";

const CreateWorkout = () => {
  const [formData, setFormData] = useState({
    title: "",
    load: "",
    reps: "",
    difficulty: "medium",
    image: null
  });


  const handleChange = (e) => {
    setFormData(prev => ({
      ...prev,
      [e.target.name]: e.target.value
    }));
  };

  const [image, setImage] = useState(null);
  const handleImageChange = (e) => {
    console.log("Selected file:", e.target.files[0]);
    setImage(e.target.files[0]);
  };

  const handleSubmit = async (e) => {
    e.preventDefault();

    try {
      {
        // Create FormData object
        const data = new FormData();

        data.append("title", formData.title);
        data.append("load", Number(formData.load));
        data.append("reps", Number(formData.reps));
        data.append("difficulty", formData.difficulty);

        if (image) {
          data.append("image", image); // must match backend field name
        }

        await api.post("/", data);
      }
      // await api.post("/", {
      //   ...formData,
      //   load: Number(formData.load),
      //   reps: Number(formData.reps),
      //   image: image
      // });

      // Reset form
      alert("Workout created!");
      setFormData({
        title: "",
        load: "",
        reps: "",
        difficulty: "medium"
      });
      setImage(null);

    } catch (err) {
      console.error(err.response?.data?.error || "Something went wrong");
    }
  };

  return (
    <form onSubmit={handleSubmit} encType="multipart/form-data">
      <h3>Create Workout</h3>

      <input
        name="title"
        placeholder="Title"
        value={formData.title}
        onChange={handleChange}
      />

      <input
        name="load"
        placeholder="Load"
        value={formData.load}
        onChange={handleChange}
      />

      <input
        name="reps"
        placeholder="Reps"
        value={formData.reps}
        onChange={handleChange}
      />

      <select
        name="difficulty"
        value={formData.difficulty}
        onChange={handleChange}
      >
        <option value="easy">Easy</option>
        <option value="medium">Medium</option>
        <option value="hard">Very Hard</option>
      </select>

      {/* File Input */}
      <input type="file" name="image" accept="image/*" onChange={handleImageChange} />

      <button type="submit">Add Workout</button>
    </form>
  );
};

export default CreateWorkout;
